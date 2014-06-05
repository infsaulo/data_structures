#include <cstdio>
#include "hash_table.h"

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

bool insert_retrieve_test()
{
    Entry *entry1 = new Entry("saulo", "value1");
    Entry *entry2 = new Entry("mark", "value2");
    Entry *entry3 = new Entry("cynthia", "value3");

    HashTable<Entry> table(2);

    table.insert(entry1);
    table.insert(entry2);
    table.insert(entry3);

    if(table.retrieve("saulo") != NULL && table.retrieve("mark") != NULL && table.retrieve("cynthia") != NULL && table.retrieve("saulo")->getValue() == "value1" && table.retrieve("mark")->getValue() == "value2" && table.retrieve("cynthia")->getValue() == "value3")
    {
        printf("TEST INSERT RETRIEVE --- OK\n");
        return true;
    }

    else
    {
        printf("TEST INSERT RETRIEVE --- FAIL\n");
        return false;
    }
}

void run_tests()
{
    if(insert_retrieve_test())
    {
        printf("ALL TESTS PASSED!\n");
    }
}

int main()
{
    run_tests();

    return 0;
}
