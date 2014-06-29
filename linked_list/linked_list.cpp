#include <cstdio>

#include "linked_list.h"

using namespace std;

Node::Node()
{
    next = NULL;
}

int Node::getData()
{
    return data;
}

void Node::setData(int data)
{
    this->data = data;
}

Node* Node::getNext()
{
    return next;
}

void Node::setNext(Node *node)
{
    next = node;
}

LinkedList::LinkedList()
{
    head = new Node();
    ptr = head;
}

void LinkedList::insert(int data)
{
    Node *newNode = new Node();
    newNode->setData(data);

    ptr->setNext(newNode);
    ptr = newNode;
}

Node* LinkedList::remove(int data)
{
    Node *auxPtr = head;
    while(auxPtr->getNext())
    {
        if(auxPtr->getNext()->getData() == data)
        {
            Node *removedNode = auxPtr->getNext();
            auxPtr->setNext(removedNode->getNext());
            return removedNode;
        }
        else
        {
            auxPtr = auxPtr->getNext();
        }
    }

    return NULL;
}

Node* LinkedList::retrieve(int data)
{
    Node *auxPtr = head;
    while(auxPtr->getNext())
    {
        if(auxPtr->getNext()->getData() == data)
        {
            return auxPtr->getNext();
        }
        auxPtr = auxPtr->getNext();
    }

    return NULL;
}

bool LinkedList::isEmpty()
{
    return head->getNext() == NULL;
}

LinkedList::~LinkedList()
{
    while(!isEmpty())
    {
        Node *removedNode = remove(head->getNext()->getData());
        delete removedNode;
    }

    delete head;
}
