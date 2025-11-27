#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <string>

typedef char Element;

class Node
{
private:
    Element val;
    int quantity;
    Node* next;
    Node* prev;
public:
    Node(Element v_);
    Node(Element e_, int q);
    ~Node();

    Node* getNext();
    Node* getPrev();
    void setNext(Node* n_);
    void setPrev(Node* n_);

    int getQuantity();
    void addQuantity(int q_);
    void subsQuantity(int q_);
    void setQuantity(int q_);
    void setVal(Element _e_);

    Element getVal();
};

#endif