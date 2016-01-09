#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <locale>
#include <sstream>

using namespace std;

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if ( first ) 
   {  
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}

int main() {
	srand(time(0));
	int n;
	cerr << "Introduzca la n: ";
	cin >> n;
	n *= 2;
	double aux = (rand()%10);
	double prop = aux/10;
	int vd = 0;
	int vnd = 0;
	string linea;
	ifstream diccionario ("diccionario.txt");
	vector<int> v;
	if (diccionario.is_open()) {
		while (getline (diccionario,linea)){
			int Number;
			if ( ! (istringstream(linea) >> Number) ) Number = 0;
		 	v.push_back(Number);
		}
	}
  bool end = false;
	//while (vd != propdicc and vnd != (n-propdicc)) {
  double rnd;
  while (not end) {
  	aux = rand()%10;
  	rnd = aux/10;
  	if( rnd < prop) {
		cout << v[rand()%(v.size())] << endl;
		++vd;
		cerr << "Encontrados: " << vd << endl;
	}
	else {
		++vnd;
		cout << rand()%999999 << endl;

	}
    if((vnd+vd) >= n) end = true;  
	}

	cerr << "Proporción de palabras del diccionari que están en el texto: " << prop*n << endl;
}