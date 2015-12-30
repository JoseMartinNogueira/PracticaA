#include <iostream>
#include <time>

using namespace std;

int main() {
	int n;
	cerr << "Introduzca la n: ";
	cin >> n;
	n *= 2;
	int r;
	for (int i = 0; i < n; ++i) {
		r = rand()%999999;
		cout << r << endl;
	}
}