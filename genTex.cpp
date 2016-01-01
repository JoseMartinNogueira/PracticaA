#include <iostream>
#include <time.h>

using namespace std;

int main() {
	int n;
	cerr << "Introduzca la n: ";
	cin >> n;
	n *= 2;
	int propdicc = rand()%n;
	int vd = 0;
	int vnd = 0;
	while (vd != propdicc and vnd != (n-propdicc)) {
		if((rand()%2) == 0) {
			cout << rand()%propdicc << endl;
			++vd;
		}
		else {
			++vnd;
			cout << rand()%999999 << endl;
		}
	}
}