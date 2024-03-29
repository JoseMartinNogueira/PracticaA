#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <locale>
#include <sstream>

#include "bloom_filter.hpp"

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
	  string s;
	  cerr << "Introdueix el nom del fitxer del diccionari amb la extensió .txt: ";
	  cin >> s;
	  ifstream dicc (s.c_str());
	  cerr << "Introdueix el nom del fitxer d'entrada amb la extensió .txt: ";
	  cin >> s;
	  ifstream ent (s.c_str());
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


	  clock_t stop_inserts = clock();

      bloom_parameters parameters;


      parameters.projected_element_count = diccionario.size();

      // error probability
      parameters.false_positive_probability = 0.0001;

      parameters.random_seed = 0xA5A5A5A5;

      parameters.compute_optimal_parameters();

      bloom_filter filter(parameters);



      for (int i = 0; i < diccionario. size(); ++i){
    	  filter.insert(diccionario[i]);
      }

      clock_t restart_inserts = clock();

      cout << "Numero de hashes utillitzades: " << parameters.optimal_parameters.number_of_hashes << endl;


      cout << "Tamany de la taula: " << parameters.optimal_parameters.table_size << endl;

  /** Cerca Hash **/
      clock_t hash_1 = clock();
      bool b;
      for (int i = 0; i < entrada.size(); ++i){
	  comp  = 0;
		b = filter.contains(entrada[i]);
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
      cout << "Temps per fer el Bloom Filter: " << (restart_inserts - stop_inserts)/double(CLOCKS_PER_SEC)*1000 << endl;
      cout << "Temps d'execució de cerca al Bloom filter: " << (hash_2-hash_1)/double(CLOCKS_PER_SEC)*1000 << endl;
      cout << "Quantitat de paraules que estaven al diccionari: " << bTrue << endl;
      cout << "Quantitat de paraules que no estaven al diccionari: " << bFalse << endl;
      //cout << "Quantitat de comparacions fetes: " << comp << endl;
      //cout << "Mitjana aritmética de comparacions totals: " << comp / numComp.size() << endl;
      cout << "Número total d'entrades diccionari: " << diccionario.size() << ", entrades text: " << entrada.size() << endl;

  }
  else cout << "Error de opertura de ficheros \n";



}
