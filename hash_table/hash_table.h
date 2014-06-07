#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <vector>

using namespace std;

// Class T must implement getKey, getValue, setKey, setValue, as it need to be a <key, value> object, and key must be a string. Use T as a boost pointer of the  type you desire.

template<class T>
class HashTable
{
    private:
    shared_ptr< vector< vector<T> > > table;
    int size;

    public:
    
    HashTable(int size);
    void insert(T entry);
    T retrieve(string key);
    int hashFunction(string key);
};
#include "hash_table.cpp"

#endif
