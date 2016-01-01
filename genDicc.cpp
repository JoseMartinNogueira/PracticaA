#include <iostream>
#include <time.h>
#include <vector>
using namespace std;


void fusiona(vector<int>& v, int e, int m, int d) {
    int n = d - e + 1;
    vector<int> aux(n);
    int i = e;
    int j = m + 1;
    int k = 0;
    // Inv: aux[0..k-1] es la fusio de v[e..i-1] i v[m+1..j-1]
    while (i <= m and j <= d) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            ++i;
        }
        else {
            aux[k] = v[j];
            ++j;
        }
        ++k;
    }
    while (i <= m) {
        aux[k] = v[i];
        ++k;
        ++i;
    }
    while (j <= d) {
        aux[k] = v[j];
        ++k;
        ++j;
    }
    for (k = 0; k < n; ++k) v[k + e] = aux[k];
}

// Pre: 0<=e<=d<v.size()
// Post: els elements de v[e..d] son els inicials, pero ordenats creixentment
void ordena_per_fusio(vector<int>& v, int e, int d) {
    if (e < d) {
        int m = (e + d)/2;
        ordena_per_fusio(v, e, m);
        ordena_per_fusio(v, m + 1, d);
        fusiona(v, e, m, d);
    }
}


int main() {
	int n;
	cin >> n;
	int r;
	vector<int> d;
	bool b = false;
	while(d.size() != n) {
		r = rand()%999999;
		for(int i = 0; i < d.size() and not b; ++i) {
			if(r == d[i]) b = true;
		}
		if (not b) d.push_back(r);
		b = false;
	}
	ordena_per_fusio(d,0,d.size()-1);
	for(int i = 0; i < n; ++i) cout << d[i] << endl;
}

