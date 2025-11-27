/*
Implementación TAD List - Estructuras Enlazadas Circulares Dobles
Curso Estructura de Datos

Abril 22 de 2024
 */

#ifndef LIST_H
#define LIST_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Node.h"

using namespace std;

class List{
  private:
    Node* first;

  public:
     List();
     void push_back(Element);
     void insert(Element, int);
     void remove(int);
     Element at(int);
     void set(int, Element);
     int size();
     bool empty();
     void displayList();
};

#endif