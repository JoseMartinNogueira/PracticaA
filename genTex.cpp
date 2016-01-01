#include <iostream>
#include <time>
#include <fstream>
#include <string>

using namespace std;

int main() {
	int n;
	cerr << "Introduzca la n: ";
	cin >> n;
	n *= 2;
	int propdicc = rand()%n;
	int vd = 0;
	int vnd = 0;
	string linea;
	istream diccionario ("diccionario.txt");
	vector<int> v;
	if (diccionario.is_open()) {
		while (getline (diccionario,linea)) v.push_back(stoi(linea));
	}

	while (vd != propdicc and vnd != (n-propdicc)) {
		if((rand()%2) == 0) {
			cout << v[rand()%(v.size())] << endl;
			++vd;
		}
		else {
			++vnd;
			cout << rand()%999999 << endl;
		}
	}
}