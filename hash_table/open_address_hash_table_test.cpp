#include <cstdio>
#include "open_address_hash_table.h"

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


bool resize_test()
{
    HashTable< shared_ptr<Entry> > table(3);

    shared_ptr<Entry> entry1(new Entry("saulo", "value1"));
    shared_ptr<Entry> entry2(new Entry("mark", "value2"));
    shared_ptr<Entry> entry3(new Entry("cynthia", "value3"));

    table.insert(entry1);
    if(table.getLoadFactor() > 0.5)
    {
        printf("TEST RESIZE --- FAIL #1\n");
        return false;
    }

    table.insert(entry2);
    if(table.getLoadFactor() < 0.5 || table.getLoadFactor() > 0.8)
    {
        printf("TEST RESIZE --- FAIL #2\n");
        return false;
    }

    // Get resized from now
    table.insert(entry3);
    if(table.getLoadFactor() < 0.5 || table.getLoadFactor() > 0.8)
    {
        printf("TEST RESIZE --- FAIL #3 %f\n", table.getLoadFactor());
        return false;
    }

    if(table.retrieve("saulo") && table.retrieve("mark") && table.retrieve("cynthia") && table.retrieve("saulo")->getValue() == "value1" && table.retrieve("mark")->getValue() == "value2" && table.retrieve("cynthia")->getValue() == "value3")
    {
        printf("TEST RESIZE --- OK\n");
        return true;
    }

}

bool insert_test()
{
    HashTable< shared_ptr<Entry> > table(3);

    shared_ptr<Entry> entry1(new Entry("saulo", "value1"));
    shared_ptr<Entry> entry2(new Entry("mark", "value2"));
    shared_ptr<Entry> entry3(new Entry("cynthia", "value3"));

    table.insert(entry1);
    table.insert(entry2);
    table.insert(entry3);

    if(table.getLoadFactor() >= 0.5)
    {
        printf("TESTE INSERT --- OK\n");
        return true;
    }
    else
    {
        printf("TESTE INSERT --- FAIL %f\n", table.getLoadFactor());
        return false;
    }
}

bool retrieve_test()
{
    HashTable< shared_ptr<Entry> > table(3);

    shared_ptr<Entry> entry1(new Entry("saulo", "value1"));
    shared_ptr<Entry> entry2(new Entry("mark", "value2"));
    shared_ptr<Entry> entry3(new Entry("cynthia", "value3"));
 
    table.insert(entry1);
    table.insert(entry2);
    table.insert(entry3);

    shared_ptr<Entry> retrieved1 = table.retrieve("mark");
    shared_ptr<Entry> retrieved2 = table.retrieve("cynthia");

    if(retrieved1 && retrieved2 && retrieved1->getValue() == "value2" && retrieved2->getValue() == "value3")
    {
        printf("TEST RETRIEVE --- OK\n");
        return true;
    }
    else
    {
        printf("TEST RETRIEVE --- FAIL");
        return false;
    }

}

void run_tests()
{
    if(insert_test() && retrieve_test() && resize_test())
    {
        printf("All tests passed!\n");
    }
}

int main()
{
    run_tests();
    return 0;
}
