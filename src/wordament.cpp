/**
 *
 *
 *
 *  @author Boopathi Rajaa <http://boopathi.in/>
 *  @version 0.1
 * 
 *  @copyright Copyright (c) 2012 Boopathi Rajaa <http://boopathi.in/>
 *  @license <http://www.opensource.org/licenses/mit-license.html>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 *
 *  CHANGES:
 * 
 */

#include "./wordament.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#define REP(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define FOR(i,n) REP(i,0,n)
#define THROW_RAW(str) ThrowException(Exception::Error(str))
#define THROW(str) THROW_RAW(String::New(str))
#define PB push_back
using namespace v8;
using namespace node;
using namespace std;

//First things are first
//Trie definitions
//class Node
Node::Node() { ch=' '; m=false; }
Node::~Node() { }
//getters
char Node::get() { return ch; }
bool Node::end() { return m; }
Node* Node::find(char c) {
    int l = children.size();
    FOR(i,l) {
        Node* tmp = children[i];
        if(tmp->get() == c) return tmp;
    }
    return NULL;
}
vector<Node*> Node::getChildren() { return children; }
//setters
void Node::set(char c) { ch=c; }
void Node::mark() { m=true; }
void Node::append(Node* child) { children.PB(child); }

//class Trie
Trie::Trie() { root=new Node(); }
Trie::~Trie() { }

void Trie::add(string s) {
    Node* current = root;
    int l = s.length();
    if(l == 0) return current->mark();
    FOR(i,l) {
        Node* child = current->find(s[i]);
        if(child != NULL) current=child;
        else {
            Node* tmp = new Node();
            tmp->set(s[i]);
            current->append(tmp);
            current=tmp;
        }
        if(l-1 == i) current->mark();
    }
}

bool Trie::search(string s) {
    Node* current = root;
    int l = s.length();
    while(current != NULL) {
        FOR(i,l) {
            Node* tmp = current->find(s[i]);
            if(tmp == NULL) return false;
            current=tmp;
        }
        if(current->end()) return true;
        else return false;
    }
    return false;
}

//Matrix
Matrix::Matrix() {
	char pool[] = {"abcdefghijklmnopqusrtuvwxyz"};
	vector<char> p;	FOR(i,26) p.PB(pool[i]);
	random_shuffle(p.begin(),p.end());
	FOR(i,4) {
		FOR(j,4) M[i][j] = p[j];
		random_shuffle(p.begin(), p.end());
	}
}
Matrix::Matrix(char (&m)[4][4]) {
	FOR(i,4) FOR(j,4) M[i][j] = m[i][j]; //copy //don't refer
}
Matrix::~Matrix() { }

void Matrix::get(char (&s)[4][4]) {
	FOR(i,4) FOR(j,4) s[i][j] = M[i][j]; // copy the values
}

string Matrix::get() {
	string ret("");
	FOR(i,4) ret+= string(M[i], 0, 4) + string(",");
	return ret;
}

bool Matrix::dfs(char s[40], int l, int x, int i, int j, bool (&v)[4][4]) {
	if(i<0 || i>3 || j<0 || j>3) return false; //boundary
	if(v[i][j]) return false;
	if(s[x] == M[i][j]) {
		if(x==l) return true;
		v[i][j]=true;
		bool r = dfs(s,l,x+1,i-1,j-1,v) ||	// left top
			dfs(s,l,x+1,i-1,j,v) || 		// top
			dfs(s,l,x+1,i-1,j+1,v) || 		// right top
			dfs(s,l,x+1,i,j-1,v) || 		// left
			dfs(s,l,x+1,i,j+1,v) || 		// right
			dfs(s,l,x+1,i+1,j-1,v) || 		// left bottom
			dfs(s,l,x+1,i+1,j,v) || 		// bottom
			dfs(s,l,x+1,i+1,j+1,v); 		// right bottom
		v[i][j]=false; //backtrack
		return r;
	}
	else return false;
}

bool Matrix::search(string s) {
	int l = s.length();
	bool v[4][4]; FOR(i,4) FOR(j,4) v[i][j]=false;
	//find the starting points
	FOR(i,4) FOR(j,4) if(s[0] == M[i][j]) 
		if(dfs(strdup(s.c_str()),l-1,0,i,j,v)) return true;
	return false;
}

//sort by string length
bool sort_by_length(string a, string b) {
	return a.length() < b.length();
}

//Game instances
Game::Game() {
	//Make the matrix
	
	//MATRIX INIT BEGIN
	char buffer[25];
	M = new Matrix();
	db = new Trie();
	string file("./wordlist");
	ifstream ff(file.c_str());
	while(true) {
		ff>>buffer;
		if(M->search(string(buffer))) { db->add(string(buffer)); Solution.PB(buffer); }
		if(ff.eof()) break;
	}
	sort(Solution.begin(), Solution.end(), sort_by_length);
	//MATRIX INIT END
}
Game::~Game() { }

//getters
Handle<Value> Game::matrix() {
	return String::New( (M->get()).c_str() );
}

Handle<Value> Game::solution() {
	int l=Solution.size();
	Local<Array> found = Array::New(l);
	FOR(i,l) found->Set(i, String::New(Solution[i].c_str()));
	return found;
}

Handle<Value> Game::lookup(const Arguments& args) {
	HandleScope scope;
	if(args.Length() < 1) return THROW("getMatrix: requires atleast 1 argument");
	if(args[0]->IsString()) {
		String::Utf8Value param(args[0]->ToString());
		string query = string(*param);
		if(M->search(query) && db->search(query)) return True();
		return False();
	}
	return THROW("getMatrix: requires a string argument");
}

Handle<Value> Game::search(const Arguments& args, Game *it) {
	return True();
}

//Finally the node part
void Wordament::Init(Handle<Object> target) {
	HandleScope scope;
	//Set all handlers accessible by JavaScript
	//NODE_SET_METHOD(target, "getMatrix", Wordament::getMatrix);
	//NODE_SET_METHOD(target, "search", Wordament::search);
	//NODE_SET_METHOD(target, "solution", Wordament::solution);
	NODE_SET_METHOD(target, "create", Wordament::create);
}

Handle<Value> Wordament::create(const Arguments& args) {
	HandleScope scope;
	Game g;// = new Game();
	
	Local<Object> game = Object::New();
	game->Set(String::NewSymbol("matrix"), g.matrix() );
	game->Set(String::NewSymbol("solution"), g.solution() );

	Local<FunctionTemplate> stpl = FunctionTemplate::New(Game::search, &g);
	//Local<Function> search = stpl->GetFunction();
	//search->SetName(String::NewSymbol("search"));
	
	//game->Set(String::NewSymbol("search"), search);
	
	//Local<Function> matrix = FunctionTemplate::New(g->matrix)->GetFunction();
	//matrix->SetName(String::NewSymbol("matrix"));
	//game->Set(String::NewSymbol("matrix"), FunctionTemplate::New(g->matrix)->GetFunction());
	//game->Set(String::NewSymbol("search"), FunctionTemplate::New(g->search)->GetFunction());
	return scope.Close(game);
}
/*
Handle<Value> Wordament::solution(const Arguments& args) {
	HandleScope scope;
	int l = Solution.size();
	Local<Array> found = Array::New(l);
	FOR(i,l) found->Set(i, String::New(Solution[i].c_str()));
	return scope.Close(found);
}

Handle<Value> Wordament::getMatrix(const Arguments& args) {
	HandleScope scope;
	return scope.Close(String::New( (M->get()).c_str() ));
}
*/
/*
W::W() { g = new Game(); }
W::~W() { delete g; }

Game* W::GameObject() { return g; }

W::Initialize(Handle<Object> target) {
	HandleScope scope;
	
	Local<FunctionTemplate> tmpl = FunctionTemplate::New(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	
	SetPrototypeMethod(t, "game", GameObject);
	
	target->Set(String::NewSymbol("Wordament"), t->GetFunction());
}

Handle<Value> W::New(const Arguments& args) {
	HandleScope scope;
	
}
*/
extern "C" {
	//just a wrapper - don't worry about a thing
	void init(Handle<Object> target) {
		Wordament::Init(target);
	}
	NODE_MODULE(wordament, init);
}
