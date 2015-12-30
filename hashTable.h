#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>
#include <string>
#include <vector>
using namespace std;

class hashTable {
	public:
		hashTable(int size);
		bool contains(const int &x);
		bool insert(const int &x);
	private:
		vector<list<int> > theLists;
		int currentSize;
		int tableSize;
		int hash(const int &x);
	};
	
#endif