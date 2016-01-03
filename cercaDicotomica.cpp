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

bool cerca_dicotomica(const vector <int> diccionario, int e, int d, int x, int &comp){
	if(e > d){
    ++comp;
    return false;
  }
	int mid = (e+d)/2;
	if (diccionario[mid] == x){
    ++comp;
    return true;
  }
	else if (x < diccionario[mid]) return cerca_dicotomica(diccionario, e, mid-1, x, ++comp);
	else if (x > diccionario[mid]) return cerca_dicotomica(diccionario,mid+1, d, x, ++comp);
}

int main() {
  clock_t start_s = clock();
  int comp, bTrue, bFalse;
  comp = bTrue = bFalse = 0;
  string lineD, lineE;
  vector <int> diccionario; // Tots els números del fitxer diccionario.txt
  vector <int> entrada; // Tots els números del fitxer entrada.txt
  vector <int> numComp; // Tots els números de les comparacions de cada element d'entrada
  ifstream dicc ("diccionario.txt");
  ifstream ent ("entrada.txt");
  if (dicc and ent) {
    /** Insercció dels valors del fitxers als corresponents vectors **/
    clock_t entrada_1 = clock();
    while (getline(dicc, lineD) and getline(ent, lineE)) {
			string Text = lineD.c_str();
			string Text2 = lineE.c_str();
			int Number;
			int Number2;
			if ( ! (istringstream(Text) >> Number) ) Number = 0;
			if ( ! (istringstream(Text2) >> Number2) ) Number2 = 0;
    	diccionario.push_back(Number);
    	entrada.push_back(Number2);
    }
	  while (getline(ent, lineE)) {
			string Text = lineE.c_str();
			int Number;
			if ( ! (istringstream(Text) >> Number) ) Number = 0;
			entrada.push_back(Number);
		}
    dicc.close();
    ent.close();
    clock_t entrada_2 = clock();

    /** Cerca Hash **/
    clock_t hash_1 = clock();
    bool b;
    for (int i = 0; i < entrada.size(); ++i){
      comp  = 0;
    	b = cerca_dicotomica(diccionario,0,entrada.size()-1,entrada[i],comp);
      if (b) ++bTrue;
      else ++bFalse;
      numComp.push_back(comp);
    }

    /**  Numero de comparacions i average **/
    comp = 0;
    for (int i = 0; i < numComp.size(); ++i) comp += numComp[i];

    clock_t hash_2 = clock();
    clock_t stop_s=clock();
    cout << "Temps total del programa: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps de lectura dels fitxers: " << (entrada_2-entrada_1)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps d'execució de l'algoritme de Cerca Dicotómica: " << (hash_2-hash_1)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Quantitat de paraules que estaven al diccionari: " << bTrue << endl;
    cout << "Quantitat de paraules que no estaven al diccionari: " << bFalse << endl;
    cout << "Quantitat de comparacions fetes: " << comp << endl;
    cout << "Mitjana aritmética de comparacions totals: " << comp / numComp.size() << endl;
    cout << "Número total d'entrades diccionari: " << diccionario.size() << ", entrades text: " << entrada.size() << endl;

  }
  else cout << "Error de opertura de ficheros \n";



}
