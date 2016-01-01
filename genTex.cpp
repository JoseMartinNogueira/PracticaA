#include <iostream>
#include <time>

using namespace std;

int main() {
	int n;
	cerr << "Introduzca la n: ";
	cin >> n;
	n *= 2;
	int propdicc = rand()%n;
	bool end();
	int vd = 0;
	int vnd = 0;
	while (vd != propdicc and vnd != (n-propdicc)) {
		if((rand()%2) == 0) {
			cout >> rand()%propdicc;
			++vd;
		}
		else {
			++vnd;
			cout >> rand()%999999;
		}
	}
}