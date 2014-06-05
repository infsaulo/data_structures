#include <cstdio>
#include <string>
#include <vector>

#include "open_address_hash_table.h"

using namespace std;

template <class T>
HashTable<T>::HashTable(int size)
{
    table = new vector<T*>(size, NULL);
    this->size = size;
    loadFactor = 0;
}

template <class T>
void HashTable<T>::insert(T *element)
{
    int hashedPosition = hashFunction(element->getKey());

    while((*table)[hashedPosition] != NULL)
    {
        hashedPosition++; // linear hashing to deal with colision
        hashedPosition %= size;
    }

    (*table)[hashedPosition] = element;
    setLoadFactor(getLoadFactor() + 1.0/size);

    // Verify the load factor. Idealy it can't be higher than 80%
    if(getLoadFactor() > 0.8)
    {
        resize();
    }
}

// Resize to turn down the load factor to 0.5
template <class T>
void HashTable<T>::resize()
{
    int newSize = (int)((getLoadFactor()/0.5) * size);
    size = newSize;
    setLoadFactor(0.0);

    vector<T*> *resizedTable = new vector<T*>(size, NULL);
    for(typename vector<T*>::iterator it = table->begin(); it != table->end(); it++)
    {
        int hashedPosition = hashFunction((*it)->getKey());
        while((*resizedTable)[hashedPosition] != NULL)
        {
            hashedPosition++;
            hashedPosition %= size;
        }

        (*resizedTable)[hashedPosition] = *it;
        setLoadFactor(getLoadFactor() + 1.0/size);
    }

    delete table;
    table = resizedTable;
}

template <class T>
float HashTable<T>::getLoadFactor()
{
    return loadFactor;
}

template <class T>
void HashTable<T>::setLoadFactor(float loadFactor)
{
    this->loadFactor = loadFactor;
}

template <class T>
T* HashTable<T>::retrieve(string key)
{
    int hashedPosition = hashFunction(key);
    int originHashedPosition = hashedPosition;

    while((*table)[hashedPosition]->getKey() != key)
    {
        hashedPosition++;
        hashedPosition %= size;
        if(hashedPosition == originHashedPosition)
        {
            return NULL;
        }
    }

    return (*table)[hashedPosition];
}

template <class T>
int HashTable<T>::hashFunction(string key)
{
    int value=0;
    for(int index=0; index < key.size(); index++)
    {
        value += key[index] * (index + 1);
    }

    value %= size;
    return value;
}

template <class T>
HashTable<T>::~HashTable()
{
    for(int index=0; index < size; index++)
    {
        delete (*table)[index];
    }

    delete table;
}
