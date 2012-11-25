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

int main() {
	int n=4;
	char a[5][5];
	FOR(i,n) FOR(j,n) cin>>a[i][j];
	ifstream words("./wordlist");
	return 0;
}

