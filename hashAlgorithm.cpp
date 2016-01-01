#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>
#include <list> 
#include "hashTable.h"


using namespace std;

hashTable::hashTable(int size) {
  theLists.resize(size);
  currentSize = 0;
  tableSize = size; 
}

bool hashTable::contains(const int &x) {
  const list<int> & whichList = theLists[hash(x)];
  return find(whichList.begin(), whichList.end(), x) != whichList.end();
}


bool hashTable::insert(const int &x) {
  int hashVal = hash(x);
  cout << "ID: " << x << " - Hash Value: " << hashVal << endl;
  list<int> & iList = theLists[hashVal];
  if(find(iList.begin(), iList.end(), x) != iList.end()) return false;
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
    while (getline(dicc, lineD) and getline(ent, lineE)) {
    	diccionario.push_back(stoi(lineD));
    	entrada.push_back(stoi(lineE));
    }
  	while (getline(ent, lineE)) entrada.push_back(stoi(lineE));
      dicc.close();
      ent.close();

      hashTable htab(diccionario.size());
      for (int i = 0; i < diccionario.size(); ++i) htab.insert(diccionario[i]);

      for (int i = 0; i < entrada.size(); ++i) cout << htab.contains(entrada[i]) << endl;


    }
  else cout << "Error de opertura de ficheros \n";

  int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

}