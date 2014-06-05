#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <vector>

using namespace std;

// Class T must implement getKey, getValue, setKey, setValue, as it need to be a <key, value> object, and key must be a string.
template<class T>
class HashTable
{
    vector< vector<T*> > *table;
    int size;

    public:
    
    HashTable(int size);
    void insert(T *entry);
    T* retrieve(string key);
    int hashFunction(string key);
    ~HashTable();
};
#include "hash_table.cpp"

#endif