#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class Entry
{
    string key;
    string value;

    public:
    Entry(string key, string value);
    void setKey(string key);
    void setValue(string value);
    string getKey();
    string getValue();
};

Entry::Entry(string key, string value)
{
    setKey(key);
    setValue(value);
}

void Entry::setKey(string key)
{
    this->key = key;
}

void Entry::setValue(string value)
{
    this->value = value;
}

string Entry::getKey()
{
    return key;
}

string Entry::getValue()
{
    return value;
}

class HashTable
{
    float loadFactor;
    int size;
    vector<Entry*> *table;

    public:

    HashTable(int size);
    void insert(Entry *element);
    Entry* retrieve(string key);
    int hashFunction(string key);
    float getLoadFactor();
    void setLoadFactor(float loadFactor);
    void resize();
    ~HashTable();
};

HashTable::HashTable(int size)
{
    table = new vector<Entry*>(size, NULL);
    this->size = size;
    loadFactor = 0;
}

void HashTable::insert(Entry *element)
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
void HashTable::resize()
{
    int newSize = (int)((getLoadFactor()/0.5) * size);
    size = newSize;
    setLoadFactor(0.0);

    vector<Entry*> *resizedTable = new vector<Entry*>(size, NULL);
    for(vector<Entry*>::iterator it = table->begin(); it != table->end(); it++)
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

float HashTable::getLoadFactor()
{
    return loadFactor;
}

void HashTable::setLoadFactor(float loadFactor)
{
    this->loadFactor = loadFactor;
}

Entry* HashTable::retrieve(string key)
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

int HashTable::hashFunction(string key)
{
    int value=0;
    for(int index=0; index < key.size(); index++)
    {
        value += key[index] * (index + 1);
    }

    value %= size;
    return value;
}

HashTable::~HashTable()
{
    for(int index=0; index < size; index++)
    {
        delete (*table)[index];
    }

    delete table;
}
