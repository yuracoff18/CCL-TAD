#include "Node.h"

Node::Node(Element e_) {
    this->val = e_;
    this->next = NULL;
    this->prev = NULL;
    this->quantity = 1;
}

Node::Node(Element e_, int q) {
    this->val = e_;
    this->next = NULL;
    this->prev = NULL;
    this->quantity = q;
}

Node::~Node() = default;

Node* Node::getNext() {
    return this->next;
}

Node* Node::getPrev() {
    return this->prev;
}

Element Node::getVal() {
    return this->val;
}

int Node::getQuantity() {
    return this->quantity;
}

void Node::setNext(Node* n_) {
    this->next = n_;
}

void Node::setPrev(Node* n_) {
    this->prev = n_;
}

void Node::addQuantity(int q_) {
    this->quantity += q_;
}

void Node::subsQuantity(int q_) {
    this->quantity -= q_;
}

void Node::setQuantity(int q_) {
    this->quantity = q_;
}

void Node::setVal(Element _e_) {
    this->val = _e_;
}