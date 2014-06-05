#ifndef _OPEN_ADDRESS_HASH_TABLE_H_
#define _OPEN_ADDRESS_HASH_TABLE_H_

#include <vector>

using namespace std;

// T must be a <key, value> entry being key a string. T must implements getKey, getVale, setKey, setValue.
template<class T>
class HashTable
{
    float loadFactor;
    int size;
    vector<T*> *table;

    public:

    HashTable(int size);
    void insert(T *element);
    T* retrieve(string key);
    int hashFunction(string key);
    float getLoadFactor();
    void setLoadFactor(float loadFactor);
    void resize();
    ~HashTable();
};
#include "open_address_hash_table.cpp"

#endif
