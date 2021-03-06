#include <cstdio>
#include <vector>
#include <string>

#include "hash_table.h"

using namespace std;


template<class T>
HashTable<T>::HashTable(int size)
{
    this->size = size;
    table = shared_ptr< vector< vector<T> > >(new vector< vector<T> >(size, vector<T>()));
}

template <class T>
void HashTable<T>::insert(T entry)
{
    int hashedPosition = hashFunction(entry->getKey());

    (*table)[hashedPosition].push_back(entry);
}

template <class T>
T HashTable<T>::retrieve(string key)
{
    int hashedPosition = hashFunction(key);

    for(typename vector<T>::iterator it = (*table)[hashedPosition].begin(); it != (*table)[hashedPosition].end(); it++)
    {
        if((*it)->getKey() == key)
        {
            return *it;
        }
    }

    return (T)NULL;
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
