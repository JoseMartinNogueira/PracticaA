#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> d;
	int r;
	bool b = false;
	while(d.size() != n) {
		r = rand()%999999;
		for(int i = 0; i < d.size() and not b; ++i) {
			if(r == d[i]) b = true;
		}
		if (not b) d.push_back(r);
		b = false;
	}
	for(int i = 0; i < n; ++i) cout << d[i] << endl;
}
