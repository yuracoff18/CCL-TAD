/*
Implementación TAD List - Estructuras Enlazadas Circulares Dobles
Curso Estructura de Datos

Abril 10 de 2024
 */

#include "List.h"

// T(n) E O(1)
List::List(){
  first = NULL;
}

// T(n) E O(1)
void List::push_back(Element e){
  Node* n = new Node(e);
  Node* last;
  
  if(first == NULL){
    first = n;
    first->setPrev(n);
    first->setNext(n);
  }
  else{
    last = first->getPrev();
    last->setNext(n);
    n->setPrev(last);
    n->setNext(first);
    first->setPrev(n);
  }
}

// Peor caso: cuando se inserta en la última posición T(n) E O(n)
// Mejor caso: cuando se inserta en la primera posición T(n) E O(1)

// De manera general se puede decir T(n) E O(pos)
void List::insert(Element e, int pos){
  Node* n = new Node(e);
  Node* tmp = first;
  int k;

  if(pos == 0){
    n->setNext(first);
    n->setPrev(first->getPrev());
    first->getPrev()->setNext(n);
    first->setPrev(n);
    first = n;
  }
  else{
    k = 0;
    while(k < pos - 1){
      tmp = tmp->getNext();
      ++k;
    }
    n->setNext(tmp->getNext());
    n->setPrev(tmp);
    tmp->getNext()->setPrev(n);
    tmp->setNext(n);
  }
}

// Peor caso: cuando se inserta en la última posición T(n) E O(n)
// Mejor caso: cuando se inserta en la primera posición T(n) E O(1)

// De manera general se puede decir T(n) E O(pos)
void List::remove(int pos){
  Node *tmp, *tmp2, *tmp3;
  int k;

  if(pos == 0){
    tmp = first;
    tmp2 = first->getNext();
    tmp3 = first->getPrev();
    tmp2->setPrev(tmp3);
    tmp3->setNext(tmp2);
    first = tmp2;
    delete tmp;
  }
  else{
    k = 0;
    tmp = first;
    while(k < pos - 1){
      tmp = tmp->getNext();
      ++k;
    }
    tmp2 = tmp->getNext();
    tmp3 = tmp2->getNext();
    tmp->setNext(tmp3);
    //if(tmp3 != NULL)
    tmp3->setPrev(tmp);
    delete tmp2;
  }
}

// Peor caso: cuando se consulta la última posición T(n) E O(n)
// Mejor caso: cuando se consulta  la primera posición T(n) E O(1)

// De manera general se puede decir T(n) E O(pos)
Element List::at(int pos){
  Node* tmp = first;
  int k = 0;
  Element ans;
  
  while(k < pos){
     tmp = tmp->getNext();
     ++k;
  }
  ans = tmp->getVal();
  return ans;
}

// Peor caso: cuando se cambia la última posición T(n) E O(n)
// Mejor caso: cuando se cambia la primera posición T(n) E O(1)

// De manera general se puede decir T(n) E O(pos)
void List::set(int pos, Element e){
  Node* tmp = first;
  int k = 0;
  
  while (k < pos){
    tmp = tmp->getNext();
    k++;
  }
  tmp->setVal(e);
}

// T(n) E O(n)
int List::size(){
  Node* tmp = first;
  int ans = 0;
  bool flag = (tmp != NULL);

  while(tmp != first || flag){
     tmp = tmp->getNext();
     flag = false;
     ++ans;
  }

  return ans;
}

// T(n) E O(1)
bool List::empty(){
  bool ans = first == NULL;
  return ans;
}

void List::displayList() {
  int s = this->size();
  printf("< ");
  for (int i = 0; i < s; i++)
  {
    printf("%d ", this->at(i));
  }
  printf(">\n");
}
