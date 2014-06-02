#include <cstdio>
#include <vector>
#include <string>

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
    vector< vector<Entry*> > *table;
    int size;

    public:
    
    HashTable(int size);
    void insert(Entry *entry);
    Entry* retrieve(string key);
    int hashFunction(string key);
    ~HashTable();
};

HashTable::HashTable(int size)
{
    this->size = size;
    table = new vector< vector<Entry*> >(size, vector<Entry*>());
}

void HashTable::insert(Entry *entry)
{
    int hashedPosition = hashFunction(entry->getKey());

    (*table)[hashedPosition].push_back(entry);
}

Entry* HashTable::retrieve(string key)
{
    int hashedPosition = hashFunction(key);

    for(vector<Entry*>::iterator it = (*table)[hashedPosition].begin(); it != (*table)[hashedPosition].end(); it++)
    {
        if((*it)->getKey() == key)
        {
            return *it;
        }
    }

    return NULL;
}

int HashTable::hashFunction(string key)
{
    int hashValue = 0;
    for(int index = 0; index < key.size(); index++)
    {
        hashValue += (int)key[index] * (index + 1);
    }

    hashValue %= size;

    return hashValue;
}

HashTable::~HashTable()
{
    for(vector< vector<Entry*> >::iterator it = table->begin(); it != table->end(); it++)
    {
        for(int index = 0; index < it->size(); index++)
        {
            delete (*it)[index];
        }
    }

    delete table;
}
