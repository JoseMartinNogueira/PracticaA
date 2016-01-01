#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

bool cerca_dicotomica(vector <int> &diccionario, int e, int d, int x){
	if(e > d) return false;
	int mid = (e+d)/2;
	if (diccionario[mid] == x) return true;
	else if (x < mid) return cerca_dicotomica(diccionario, e, mid-1, x);
	else if (x > mid) return cerca_dicotomica(diccionario,mid+1, d, x);
}

int main() {
  clock_t start_s = clock();	
  string lineD, lineE;
  vector <int> diccionario;
  vector <int> entrada;
  ifstream dicc ("diccionario.txt");
  ifstream ent ("entrada.txt");
  if (dicc and ent) { 
  	// Oberts be, ENTRA

    while (getline(dicc, lineD) and getline(ent, lineE)) {
    	diccionario.push_back(stoi(lineD));
    	entrada.push_back(stoi(lineE));
    }
	while (getline(ent, lineE)) entrada.push_back(stoi(lineE));
    dicc.close();
    ent.close();

    bool b;
    for (int i = 0; i < entrada.size(); ++i){
    	b = cerca_dicotomica(diccionario,0,entrada.size()-1,entrada[i]);
    	if (b) cout << "Trobat" << endl;
    }
    
  }
  else cout << "Error de opertura de ficheros \n";

  int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

}