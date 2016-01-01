#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <list> 
#include "hashTable.h"


using namespace std;

int comparaciones = 0; 

bool findsorted(list<int> l, int x) {
  list<int>::iterator it = l.begin();
  while(it != NULL) {
    if(*it < x) {return false;
    if(*it == x) return true;
    ++it;
    comparaciones++; // Contamos como que cada iteración del bucle es una comparación
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
  ifstream dicc ("diccionario.txt");
  ifstream ent ("entrada.txt");
  if (dicc and ent) { 
    clock_t ficheros_start = clock();
    while (getline(dicc, lineD) and getline(ent, lineE)) {
    	diccionario.push_back(stoi(lineD));
    	entrada.push_back(stoi(lineE));
    }
  	while (getline(ent, lineE)) entrada.push_back(stoi(lineE));
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
    cout << "Mitjana aritmetica de les comparacions fetes fent la taula: " << compTable/comphasht.size() <<endl;
    cout << "Quantitat de comparacions fetes a la cerca: " << compCerca <<endl;
    cout << "Mitjana aritmetica de les comparacions fetes a la cerca: " << compCerca/compvec.size() << endl;
    cout << "Número total d'entrades diccionari: " << diccionario.size() << ", entrades text: " << entrada.size() << endl;
  }
  else cout << "Error de opertura de ficheros \n";  
}