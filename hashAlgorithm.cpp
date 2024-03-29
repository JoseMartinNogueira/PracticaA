#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <locale>
#include <sstream>
#include <list> 
#include "hashTable.h"


using namespace std;

int comparaciones = 0; 

bool findsorted(list<int> l, int x) {
    list<int>::iterator it = l.begin();
  while(it != l.end()) {
    comparaciones++; // Contamos como que cada iteración del bucle es una comparación
    if(*it == x) return true;
      ++it;
    }
      return false;
}

hashTable::hashTable(int size) {
  theLists.resize(size);
  currentSize = 0;
  tableSize = size; 
}

bool hashTable::contains(const int &x) {
  const list<int> & whichList = theLists[hash(x)];
  return findsorted(whichList, x);
}


bool hashTable::insert(const int &x) {
  int hashVal = hash(x);
  cout << "ID: " << x << " - Hash Value: " << hashVal << endl;
  list<int> & iList = theLists[hashVal];
  if(findsorted(iList, x)) return false;
  iList.push_back(x);
  currentSize++;
  return true;
}

int hashTable::hash(const int &x) {
  return (x % tableSize);
}

int main() {

  clock_t start_s = clock();	
  string lineD, lineE;
  vector <int> diccionario;
  vector <int> entrada;
  string s;
  cerr << "Introdueix el nom del fitxer del diccionari amb la extensió .txt: ";
  cin >> s;
  ifstream dicc (s.c_str());
  cerr << "Introdueix el nom del fitxer d'entrada amb la extensió .txt: ";
  cin >> s;
  ifstream ent (s.c_str());
  if (dicc and ent) { 
    clock_t ficheros_start = clock();
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
    clock_t ficheros_end = clock();
    
    //Tabla Hash 
    
      vector<int> comphasht;
    clock_t hashTable_start = clock();
      hashTable htab(diccionario.size());
      for (int i = 0; i < diccionario.size(); ++i) {
          htab.insert(diccionario[i]);
          comphasht.push_back(comparaciones);
          comparaciones = 0;
      }
    clock_t hashTable_end = clock();
      
    //Hash

      int trobats = 0;
      int notrobats = 0;
      comparaciones = 0;
      vector<int> compvec;
    clock_t hash_start = clock();
      for (int i = 0; i < entrada.size(); ++i) {
        if (htab.contains(entrada[i])) ++trobats;
        else ++notrobats;
        compvec.push_back(comparaciones);
        comparaciones = 0;
      }
    clock_t hash_end = clock();


    int stop_s=clock();
    
    //Analisis final
    int comp, compTable, compCerca;
    comp = compTable = compCerca = 0;
    for(int i = 0; i < comphasht.size(); ++i) {
      compTable += comphasht[i];
      comp += comphasht[i]; 
    }
    for (int i = 0; i < compvec.size(); ++i) {
      compCerca += compvec[i];
      comp += compvec[i];
    }

    cout << "Temps total del programa: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps lecutra del fitxers: " << (ficheros_end - ficheros_start)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps total de Hash: " << (hash_end - hashTable_start)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps per fer la hash table: " << (hashTable_end - hashTable_start)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Temps per per trobar les paraules: " << (hash_end - hash_start)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Quantitat de paraules que estaven al diccionari: " << trobats << endl;
    cout << "Quantitat de paraules que no estaven al diccionari: " << notrobats << endl;
    cout << "Quantitat total de comparacions: " << comp << endl;
    cout << "Quantitat de comparacions fetes fent la taula: " << compTable << endl;
    cout << "Mitjana aritmetica de les comparacions fetes fent la taula: " << double(compTable)/double(comphasht.size()) <<endl;
    cout << "Quantitat de comparacions fetes a la cerca: " << compCerca <<endl;
    cout << "Mitjana aritmetica de les comparacions fetes a la cerca: " <<  double(compCerca)/double(compvec.size()) << endl;
    cout << "Número total d'entrades diccionari: " << diccionario.size() << ", entrades text: " << entrada.size() << endl;
  }
  else cout << "Error de opertura de ficheros \n";  
}
