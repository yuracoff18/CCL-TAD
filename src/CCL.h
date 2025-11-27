#ifndef CCL_H
#define CCL_H

#include "Node.h"
#include <vector>
#include "List.h"
#include "algorithm"

class CCL
{
private:
    Node* first;
    int lenght;
public:
    // Constructores
    CCL(); // Hecho
    CCL(const CCL& _c_); // Hecho
    CCL(std::vector<Element> v_); // Hecho

    // Destructor
    ~CCL(); // Hecho

    // Analizadores
    int size(); // Hecho
    int node_size(); // Hecho
    int getConsecutiveOcurrences(std::vector<Element> &v_); // Hecho?
    int getIndexFirstConsecutiveOcurrence(std::vector<Element> &v_); // Hecho?
    int searchElement(Element &e_); // Hecho?
    void displayCCL(); // Hecho

    // Modificadores
    void push_back(Element e_); // Hecho
    void push_back(Element e_, int q);
    void push_front(Element e_, int q);
    void push_back_node(Node* _n_); // Hecho
    void insertElement(int i_, Element e_); // Hecho
    void removeFirstOcurrence(Element e_); // Hecho
    void removeAllOcurrence(Element e_); // Hecho
    void removeBlockPosition(int i_); // Hecho
    void getLexicographicFusion(CCL _c_); // Hecho
    List expand(); // Hecho

    static void sortVectorCCL(vector<CCL> &v_);
    
    
    // Operadores
    Element operator[](int i) const; // Hecho
    CCL operator+(CCL &_c_) const; // Hecho
    bool operator==(const CCL &_e_) const; // Hecho
    bool operator<(const CCL &_e_) const; // Hecho
};


#endif