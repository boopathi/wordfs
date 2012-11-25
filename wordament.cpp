#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
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
#define DB(x) cout<<"\n"<<#x<<" = "<<(x)<<"\n";
#define CL(a,b) memset(a,b,sizeof(a))
#define PB push_back
typedef long long int int64;
typedef unsigned long long int uint64;
const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;
inline void swaps(char *x,char *y){char temp;temp=*x;*x=*y;*y=temp;}
inline void swapi(int *a,int *b){int temp;temp=*a;*a=*b;*b=temp;}
inline void swapl(int64 *a, int64 *b){int64 temp;temp=*a;*a=*b;*b=temp;}
inline void frint(int *a){
  register char c=0;while (c<33) c=getchar_unlocked();*a=0;
  while (c>33){*a=*a*10+c-'0';c=getchar_unlocked();}
}
int gcd(int a,int b) { if(a%b==0)return b; else return gcd(b,a%b); }
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

int main() {
	int n=4;
	char a[5][5];
    char buffer[40];
    int c=0;
    Trie* db = new Trie();
    while(scanf("%s", buffer) == 1) {
        db->add(string(buffer));
    }
    FOR(i,502992)
    	cout<<db->search("search")<<endl;
	return 0;
}

