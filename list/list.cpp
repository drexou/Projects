#include "list.hpp"
#include <iostream>
using namespace std;

// TODO: Insert List method definitions here.
List::List() : head{nullptr}, tail{nullptr}, len{0} { }

List::List(const List& other)
{
    len = 1;
    Node* headNode = new Node;
    headNode->data = other.head->data;
    headNode->next = nullptr;
    headNode->prev = nullptr;
    head = headNode;
    
    Node* bufNode = head;
    Node* currNode = other.head->next;

    while(currNode != nullptr)
    {
        Node* newNode = new Node;
        newNode->data = currNode->data;
        newNode->prev = bufNode;
        newNode->next = nullptr;
        bufNode->next = newNode;
        bufNode = bufNode->next;
        currNode = currNode->next;
        len += 1;
    }
    tail = bufNode;
}

List::~List()
{
    Node* currNode = head;
    while(currNode != nullptr)
    {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

List& List::operator=(const List& other)
{
    Node* currNode = head;
    while(currNode != nullptr)
    {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
    len = 1;
    Node* headNode = new Node;
    headNode->data = other.head->data;
    headNode->next = nullptr;
    headNode->prev = nullptr;
    head = headNode;
    
    Node* bufNode = head;
    currNode = other.head->next;

    while(currNode != nullptr)
    {
        Node* newNode = new Node;
        newNode->data = currNode->data;
        newNode->prev = bufNode;
        newNode->next = nullptr;
        bufNode->next = newNode;
        bufNode = bufNode->next;
        currNode = currNode->next;
        len += 1;
    }
    tail = bufNode;
    return *this;
}

unsigned List::length() const
{
    return len;
}

void List::pushFront(int data)
{
    Node* node = new Node;
    node->data = data;
    node->prev = nullptr;
    node->next = head;
    if(head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        head->prev = node;
        head = node;
    }
    len += 1;
}

void List::pushBack(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = nullptr;
    node->prev = tail;
    if(head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    len += 1;
}

void List::operator+=(int data)
{
    pushBack(data);
}

int& List::operator[](unsigned index)
{
    if(index >= len)
        throw out_of_range{"your mom"};
    unsigned currIndex = 0;
    Node* currNode = head;
    while(currIndex != index)
    {
        currNode = currNode->next;
        currIndex += 1;
    }
    return currNode->data;
}

const int& List::operator[] (unsigned index) const
{
    if(index >= len)
        throw out_of_range{"your mom"};
    unsigned currIndex = 0;
    Node* currNode = head;
    while(currIndex != index)
    {
        currNode = currNode->next;
        currIndex += 1;
    }
    return currNode->data;
}

bool List::contains(int data) const
{
    Node* currNode = head;
    while(currNode != nullptr)
    {
        if(currNode->data == data)
            return true;
        currNode = currNode->next;
    }
    return false;
}

bool List::remove(int data)
{
    Node* currNode = head;
    while(currNode != nullptr)
    {
        if(currNode->data == data)
        {
            if(currNode->next != nullptr && currNode->prev != nullptr)
            {
                currNode->next->prev = currNode->prev;
                currNode->prev->next = currNode->next;
            }
            else if(currNode->next == nullptr)
            {
                currNode->prev->next = nullptr;
                tail = currNode->prev;
            }
            else if(currNode->prev == nullptr)
            {
                currNode->next->prev = nullptr;
                head = currNode->next;
            }
            delete currNode;
            len -= 1;
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

void List::operator-=(int data)
{
    remove(data);
}

ostream& operator<< (ostream& os, const List& list)
{
    Node *currNode = list.head;
    while(currNode->next)
    {
        os <<  currNode->data << " ";
        currNode = currNode->next;
    }
    os << currNode->data << endl; 
    return os;
}
/*
int main()
{

    // List vals;
    // vals.pushBack(2);
    // vals.pushFront(3);
    // vals.remove(3);

    // List vals; 
    // for (int i = 0; i < 10; ++i) vals += i;
    // List vals2{vals};
    // vals2 -= 0;
    // vals2 -= 8;
    // vals2 -= 7;
    // cout << vals << vals2;


    // cout << vals << vals2;
    // cout << vals.length() << " " << vals2.length() << endl;



    List vals; 
    for (int i = 0; i < 10000; ++i) vals += i;
    List vals2{vals};
    vals -= 0;
    vals2 -= 9999;
    vals2 = vals;
    // vals2 -= 9999;
    // vals2 = vals;
    // vals = vals2;
    // for(int i=10; i < 10000; i++) vals -= i;
    // cout << vals.length() << ' ' << vals2.length() << endl;
    // cout << vals;
}*/