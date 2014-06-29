#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

class Node
{
    Node *next;
    int data;

    public:
    Node();
    int getData();
    void setData(int);
    Node* getNext();
    void setNext(Node*);
};

class LinkedList
{
    Node *head;
    Node *ptr;

    public:
    LinkedList();
    void insert(int);
    Node *remove(int);
    Node *retrieve(int);
    bool isEmpty();
    ~LinkedList();
};
#include "linked_list.cpp"

#endif
