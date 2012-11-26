/*
 * Author: Boopathi Rajaa <me@boopathi.in>
 * Check README.md for installation instructions
 */
#include <vector>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <climits>
#include <fstream>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(x) ((x)<0?-(x):(x))
#define FOR(i,n) for(int (i)=0;(i)<(n);(i)++)
#define REP(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define REV(i,n) for(int (i)=(n)-1;(i)>=0;(i)--)
#define GI ({int t;scanf("%d",&t);t;})
#define GF ({float t;scanf("%f",&t);t;})
#define GL ({int64 t;scanf("%ld",&t);t;})
#define CL(a,b) memset(a,b,sizeof(a))
#define PB push_back
typedef long long int int64;
typedef unsigned long long int uint64;
inline void swaps(char *x,char *y){char temp;temp=*x;*x=*y;*y=temp;}
inline void swapi(int *a,int *b){int temp;temp=*a;*a=*b;*b=temp;}
inline void swapl(int64 *a, int64 *b){int64 temp;temp=*a;*a=*b;*b=temp;}
using namespace std;
//trie
class Node {
    private:
        char ch;
        bool m;
        vector<Node*> children;
    public:
        Node() { ch = ' '; m=false; }
        ~Node() {}
        char get() { return ch; }
        void set(char c) { ch = c; }
        bool end() { return m; }
        void mark() { m = true; }
        Node* find(char c);
        void append(Node* child) { children.PB(child); }
        vector<Node*> getChildren() { return children; }
};

class Trie {
    private: 
        Node* root;
    public:
        Trie() { root = new Node(); }
        ~Trie() {}
        void add(string s);
        bool search(string s);
};

Node* Node::find(char c) {
    int l = children.size();
    FOR(i,l) {
        Node* tmp = children[i];
        if(tmp->get() == c) return tmp;
    }
    return NULL;
}

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

//Matrix - Find a string in matrix
char M[4][4];

bool dfs(char s[40], int l, int x, int i, int j, bool (&v)[4][4]) {
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

bool matrixSearch(string s) {
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

int main(int argc, char* argv[]) {
	int n=4, c=0;
    char buffer[40]; 
    vector<string> Found;
    //INPUT - matrix
    FOR(i,4) scanf("%s", M[i]);
    
    Trie* db = new Trie();
    //populate the trie
    string file(argc==2 ? argv[1] : "../wordlist");
    ifstream ff(file.c_str());
    while(true) {
    	ff>>buffer;
    	if(matrixSearch(string(buffer))) { db->add(string(buffer)); Found.PB(buffer); }
    	if(ff.eof()) break;
    }
    sort(Found.begin(), Found.end(), sort_by_length);
    FOR(i,Found.size()) cout<<Found[i]<<"; "; cout<<endl;
    cout<<"Now start searching : "<<endl;
    FOR(i,4) { FOR(j,4) cout<<M[i][j]<<" "; cout<<endl; }
    char str[20];
    scanf("%s",str);
    while(strlen(str) > 2) {
    	if(matrixSearch(string(str)) && db->search(string(str)) ) cout<<"Found"<<endl;
    	else cout<<"NOT Found"<<endl;
    	scanf("%s",str);
    }
	return 0;
}

