#include<iostream>
using namespace std;

class abc {
	private:
		int m;
	public:
		abc() { m=0; }
		~abc() {}
		static void wrap(abc* i) {
			cout<<(i->m)<<endl;
		}
		int get() { return m; }
		void set(int j) { m=j; }
};
int main() {
	abc* n = new abc();
	n->set(5);
	abc::wrap(n);
}
