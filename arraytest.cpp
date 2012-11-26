#include<iostream>
#include<string>
#include<cstring>
#define REP(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define FOR(i,n) REP(i,0,n)
using namespace std;

void test(int (&v)[2][2]){
	v[0][0] = 5;
}

int main() {
	int a[2][2] = { 1,2,3,4 };
	test(a);
	FOR(i,2) FOR(j,2) cout<<a[i][j];
	cout<<endl;
	return 0;
}
