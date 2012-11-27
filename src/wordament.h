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

#ifndef WORDAMENT_H //NOLINT
#define WORDAMENT_H "rm -rf /"

#include <v8.h>
#include <node.h>
#include <vector>
#include <string>

using namespace v8;
using namespace node;
using namespace std;

//Node stuff
class Wordament:ObjectWrap {
private:
public:
	Wordament();
	~Wordament();
	static void Init(Handle<Object>);
	static Handle<Value> search(const Arguments& args);
	static Handle<Value> getMatrix(const Arguments& args);
	static Handle<Value> solution(const Arguments& args);
};

//Trie 
class Node {
private:
    char ch;
    bool m;
    vector<Node*> children;
public:
    Node();
    ~Node();
    char get();
    void set(char c);
    bool end();
    void mark();
    Node* find(char c);
    void append(Node* child);
    vector<Node*> getChildren();
};

class Trie {
private: 
    Node* root;
public:
    Trie();
    ~Trie();
    void add(string s);
    bool search(string s);
};

//Matrix
class Matrix {
private:
	char M[4][4];
	bool dfs(char s[40],int l, int x, int i, int j, bool (&v)[4][4]);
public:
	Matrix();
	Matrix(char (&s)[4][4]);
	~Matrix();
	bool search(string s);
	void get(char (&s)[4][4]);
	string get();
};

#endif //NOLINT