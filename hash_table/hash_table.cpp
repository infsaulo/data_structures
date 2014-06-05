#include <cstdio>
#include <vector>
#include <string>

#include "hash_table.h"

using namespace std;


template<class T>
HashTable<T>::HashTable(int size)
{
    this->size = size;
    table = new vector< vector<T*> >(size, vector<T*>());
}

template <class T>
void HashTable<T>::insert(T *entry)
{
    int hashedPosition = hashFunction(entry->getKey());

    (*table)[hashedPosition].push_back(entry);
}

template <class T>
T* HashTable<T>::retrieve(string key)
{
    int hashedPosition = hashFunction(key);

    for(typename vector<T*>::iterator it = (*table)[hashedPosition].begin(); it != (*table)[hashedPosition].end(); it++)
    {
        if((*it)->getKey() == key)
        {
            return *it;
        }
    }

    return NULL;
}

template <class T>
int HashTable<T>::hashFunction(string key)
{
    int hashValue = 0;
    for(int index = 0; index < key.size(); index++)
    {
        hashValue += (int)key[index] * (index + 1);
    }

    hashValue %= size;

    return hashValue;
}

template <class T>
HashTable<T>::~HashTable()
{
    for(typename vector< vector<T*> >::iterator it = table->begin(); it != table->end(); it++)
    {
        for(int index = 0; index < it->size(); index++)
        {
            delete (*it)[index];
        }
    }

    delete table;
}
