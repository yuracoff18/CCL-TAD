#include "CCL.h"

// Constructores

// T(n) ∈ O(1)
CCL::CCL() {
    this->first = NULL;
    this->lenght = 0;
}

// ∈
// Peor caso: debe copiar todos los nodos del CCL original T(n) ∈ O(n)
// Mejor caso: cuando la lista está vacía T(n) ∈ O(1)
CCL::CCL(const CCL&_c_) {
    this->first = NULL;
    this->lenght = 0;

    if (_c_.first!=NULL)
    {
        Node* tmp = _c_.first;
        bool first = true;
        while (tmp !=  _c_.first || first)
        {
            first = false;

            this->push_back(tmp->getVal(), tmp->getQuantity());

            tmp = tmp->getNext();
        }
    }
}


// Peor caso: debe insertar todos los elementos del vector  T(n) ∈ O(n)
// Mejor caso: vector vacío  T(n) ∈ O(1)
// De manera general: T(n) ∈ O(n)
CCL::CCL(std::vector<Element> v_) {
    this->first = NULL;
    this->lenght = 0;

    for (size_t i = 0; i < v_.size(); i++)
    {
        this->push_back(v_[i]);
    }
}

// Destructor

// T(n) ∈ O(1)
CCL::~CCL() = default;

// Analizadores


// n = número total de elementos en la lista expandida 
// m = tamaño del vector v_

// Construcción de la lista seq (expandir el CCL):
//   - Recorre todos los nodos y mete cada elemento según su cantidad
//   - T(n) E O(n)

// Búsqueda de subsecuencia dentro de seq:
//   - En el peor caso, para cada posición de inicio se comparan hasta m elementos
//   - Peor caso: T(n) E O(n * m)
//   - Mejor caso: cuando no hay coincidencias y se falla rápido en la comparación inicial
//                 T(n) E O(n)

// De manera general: T(n) E O(n * m)
int CCL::getOcurrences(vector<Element> &v_) {
    int ans = 0;
    bool valid = true;

    if (this->first == nullptr || v_.empty()) {
        valid = false;
    }

    if (valid) {
        std::list<Element> seq;
        Node* tmp = this->first;
        bool first_time = true;

        while (first_time || tmp != this->first) {
            first_time = false;
            int q = tmp->getQuantity();
            int i = 0;
            while (i < q) {
                seq.push_back(tmp->getVal());
                i++;
            }
            tmp = tmp->getNext();
        }

        int m = v_.size();
        int n = seq.size();

        if (m > n) {
            valid = false;
        }

        if (valid) {
            list<Element>::iterator itStart = seq.begin();
            while (itStart != seq.end()) {
                list<Element>::iterator it = itStart;
                int k = 0;
                while (it != seq.end() && k < m) {
                    if (*it == v_[k]) {
                        k++;
                    }
                    ++it;
                }
                if (k == m) {
                    ans++;
                    itStart = it;
                } else {
                    ++itStart;
                }
            }
        }
    }
    return ans;
}


//     n = número total de elementos en la lista expandida (tamaño de seq)
//     m = tamaño del vector v_

//   Construcción de la lista seq:
//   - Recorre todos los nodos y agrega cada elemento según su cantidad
//   - T(n) ∈ O(n)

//   Búsqueda de la primera ocurrencia:
//   - En el peor caso:
//       Para cada posición de inicio itStart se recorre casi todo el resto de la lista
//       lo que genera que n + (n-1) + (n-2) + ... + 1 ∈ O(n^2)
//       T(n) ∈ O(n^2)

//   - Mejor caso: cuando la primera ocurrencia se encuentra desde el primer itStart
//     T(n) ∈ O(n)

// De manera general, la cota que domina es: T(n) ∈ O(n^2)
int CCL::getIndexFirstOcurrence(std::vector<Element> &v_) {
    int ans = -1;
    bool valid = true;

    if (this->first == nullptr || v_.empty()) {
        valid = false;
    }

    if (valid) {
        list<Element> seq;
        Node* tmp = this->first;
        bool first_time = true;

        while (first_time || tmp != this->first) {
            first_time = false;
            int q = tmp->getQuantity();
            int i = 0;
            while (i < q) {
                seq.push_back(tmp->getVal());
                i++;
            }
            tmp = tmp->getNext();
        }

        int m = v_.size();
        int n = seq.size();

        if (m > n) {
            valid = false;
        }

        if (valid) {
            list<Element>::iterator itStart = seq.begin();
            int idx = 0;
            bool found = false;

            while (itStart != seq.end() && !found) {
                list<Element>::iterator it = itStart;
                int k = 0;
                while (it != seq.end() && k < m) {
                    if (*it == v_[k]) {
                        k++;
                    }
                    ++it;
                }
                if (k == m) {
                    ans = idx;
                    found = true;
                } else {
                    ++itStart;
                    idx++;
                }
            }
        }
    }

    return ans;
}

// T(n) ∈ O(n)
// Recorre todos los nodos de la lista circular exactamente una vez
int CCL::countBlocks() {
    int ans = 0;
    Node* tmp = this->first;
    bool firstIt = true;

    while (firstIt || tmp != this->first)
    {
        firstIt = false;

        ++ans;

        tmp = tmp->getNext();
    }
    return ans;
}

// T(n) ∈ O(n)
// Recorre todos los nodos de la lista circular una sola vez
void CCL::print() {
    printf("Size = %d, Blocks = %d\n", this->lenght, this->countBlocks());

    Node* tmp = this->first;
    bool firstIt = true;

    printf("[");
    while (firstIt || tmp != this->first)
    {
        firstIt = false;
        if (tmp->getNext() == this->first)
        {
             printf("{%d, %d}", tmp->getVal(), tmp->getQuantity());
        }
        else
        {
             printf("{%d, %d},", tmp->getVal(), tmp->getQuantity());
        }
        tmp = tmp->getNext();
    }
    printf("]\n");

}
// T(n) ∈ O(1)
// Retorna directamente el atributo lenght sin recorrer la lista
int CCL::size() {
    return this->lenght;
}

//Mejor caso: cuando la lista está vacía o el vector v_ está vacío, la función retorna 
//sin hacer ningún recorrido
//          T(n) ∈ O(1)

//Peor caso: cuando todos los nodos contienen el mismo valor que el primer elemento del vector 
//El while externo recorre todos los nodos, y para cada nodo se verifican diferentes posiciones iniciales.
//Cada verificación recorre hasta m elementos de la entrada, donde m es el tamaño del vector y en el peor 
//caso se realizan verificaciones de longitud m desde cada posible posición en los n nodos.
//          T(n) ∈ O(n * m)

//De manera general se puede decir: T(n) ∈ O(n * m)
int CCL::getConsecutiveOcurrences(std::vector<Element> &v_) {
    if (this->first == nullptr || v_.empty()) {
        return 0;
    }

    int ans = 0;
    Node* tmp = this->first;
    bool first = true;

    while (first || tmp != this->first) {
        first = false;

        if (tmp->getVal() == v_[0]) {
            int q = tmp->getQuantity();

            for (int i = 0; i < q; ++i) {
                Node* aux = tmp;
                int j = i;
                int k = 0;
                bool valid_ocurrence = true;

                while (valid_ocurrence && k < v_.size()) {
                    if (aux == this->first && k > 0) {
                        valid_ocurrence = false;
                    } else if (aux->getVal() != v_[k]) {
                        valid_ocurrence = false;
                    } else {
                        ++j;
                        if (j >= aux->getQuantity()) {
                            aux = aux->getNext();
                            j = 0;
                        }
                        ++k;
                    }
                }

                if (valid_ocurrence && k == v_.size()) {
                    ++ans;
                }
            }
        }

        tmp = tmp->getNext();
    }

    return ans;
}

//Mejor caso: cuando la lista está vacía, el vector está vacío, o la primera ocurrencia del patrón
//está al inicio de la lista. La función se retorna sin recorrer toda la lista.
//          T(n) ∈ O(1)

//Peor caso: cuando la entrada no está en la lista o se encuentra al final. El while externo recorre 
//todos los nodos, y para cada nodo que coincide con el primer elemento del vector se verifican diferentes 
//posiciones iniciales.
//Cada verificación recorre hasta m elementos de la entrada, donde m es el tamaño del vector. En el peor 
//caso se realizan verificaciones de longitud m desde cada posible posición en los n nodos.
//          T(n) ∈ O(n * m)

//De manera general se puede decir: T(n) ∈ O(n * m)
int CCL::getIndexFirstConsecutiveOcurrence(std::vector<Element> &v_) {
    Node* tmp = first;
    bool first_time = true;
    bool found = false;
    int loked = 0;
    int ans = -1;

    while ((first_time || tmp != this->first) && !found)
    {
        first_time = false;
        if (tmp->getVal() == v_[0])
        {
            for (int i = 0; i < tmp->getQuantity(); i++)
            {
                int used = i + 1;
                size_t j = 1;
                Node* aux = tmp;
                bool occurrence = true;
                while (occurrence && j < v_.size())
                {
                    
                    if (aux->getVal() != v_[j])
                    {
                        occurrence = false;
                    }
                    
                    if (used >= aux->getQuantity())
                    {
                        used = 0;
                        aux = aux->getNext();
                        if (aux == this->first)
                        {
                            occurrence = false;
                        }
                        
                    }
                    used++;
                    j++;
                }

                if (occurrence)
                {
                    ans = (i + loked) - 1;
                    found = true;
                }
            }
            loked += tmp->getQuantity();
        }
        else
        {
            loked += tmp->getQuantity();
        }
        tmp = tmp->getNext();
    }

    return ans;
}

// Peor caso: cuando el elemento NO está en la lista, entonces recorre todos los nodos
//            T(n) ∈ O(n)
//
// Mejor caso: cuando el elemento está en el primer nodo 
//            T(n) ∈ O(1)
//
// De manera general: T(n) ∈ O(n)
int CCL::searchElement(Element e_) {
    int ans = 0;
    bool found = false;
    bool first_time = true;
    Node* tmp = this->first;

    while ((tmp != this->first || first_time) && !found)
    {
        first_time = false;

        if (tmp->getVal() == e_)
        {
            found = true;
        }
        else {
            ans += tmp->getQuantity();
        }

        tmp = tmp->getNext();
    }

    if (!found)
    {
        ans = -1;
    }
    

    return ans;
}

// Peor caso: cuando la lista NO está vacía, entonces recorre todos los nodos una vez
//            T(n) ∈ O(n)

// Mejor caso: cuando la lista está vacía 
//            T(n) ∈ O(1)

// De manera general: T(n) ∈ O(n)
void CCL::displayCCL() {
    bool first_time = true, empty = false;
    Node* tmp = this->first;

    if (this->first == NULL)
    {
        empty = true;
    }
    

    printf("< ");

    if (!empty)
    {
        while ((first_time || tmp != this->first))
        {
            first_time = false;
            if (tmp->getNext() != this->first)
            {
                printf("(%d, %d), ", tmp->getVal(), tmp->getQuantity());
            }
            else
            {
                printf("(%d, %d)", tmp->getVal(), tmp->getQuantity());
            }
            tmp = tmp->getNext();
        }
    }
    else
    {
        printf("CCl vacio");
    }
    printf(" >\n");
}

// Peor caso: cuando la lista NO está vacía, entonces recorre todos los nodos una vez
//            T(n) ∈ O(n)
//
// Mejor caso: cuando la lista está vacía
//            T(n) ∈ O(1)
//
// De manera general: T(n) ∈ O(n)
int CCL::node_size() {
    Node* tmp = this->first;
    int ans = 0;
    bool start = true;
    while (start || tmp != this->first)
    {
        start = false;
        ++ans;
        tmp = tmp->getNext();
    }
    return ans;
}

// Modificadores

//Mejor caso: cuando la lista está vacía o el índice es inválido.
//                  T(n) ∈ O(1)

//Peor caso: cuando la lista no está vacía y el índice es válido. 
//Expande la lista completa, elimina todos los nodos y reconstruye la estructura
//                   T(n) ∈ O(n)

//De manera general: T(n) ∈ O(n)

void CCL::set(int index, Element e_) {
    bool valid = true;

    if (this->first == nullptr) {
        valid = false;
    }

    if (index < 0) {
        valid = false;
    }

    if (valid) {
        if (index >= this->lenght) {
            valid = false;
        }
    }

    if (valid) {
        vector<Element> seq;
        seq.reserve(this->lenght);

        Node* tmp = this->first;
        bool first_time = true;

        while (first_time || tmp != this->first) {
            first_time = false;
            int q = tmp->getQuantity();
            int i = 0;
            while (i < q) {
                seq.push_back(tmp->getVal());
                i++;
            }
            tmp = tmp->getNext();
        }

        seq[index] = e_;

        if (this->first != nullptr) {
            Node* start = this->first->getNext();
            while (start != this->first) {
                Node* nxt = start->getNext();
                delete start;
                start = nxt;
            }
            delete this->first;
        }

        this->first = nullptr;
        this->lenght = 0;

        int i = 0;
        while (i < (int)seq.size()) {
            this->push_back(seq[i]);
            i++;
        }
    }
}

// Mejor caso: cuando la lista está vacía o el último nodo tiene el mismo valor e_
// Solo se hacen asignaciones y operaciones sobre punteros fijas 
//                     T(n) ∈ O(1)

// Peor caso: cuando la lista no está vacía y el último nodo tiene un valor distinto a e_
// Se crea un nuevo nodo y se actualizan un número constante de punteros 
//                     T(n) ∈ O(1)

// De manera general: T(n) ∈ O(1)
void CCL::push_back(Element e_) {
    if (this->first == NULL)
    {
        this->first = new Node(e_);
        this->first->setNext(this->first);
        this->first->setPrev(this->first);
    }
    else
    {
        Node* tmp = this->first->getPrev();
        if (tmp->getVal() == e_)
        {
            tmp->addQuantity(1);
        }
        else
        {
            Node* aux = new Node(e_);
            aux->setPrev(tmp);
            tmp->setNext(aux);

            aux->setNext(this->first);
            this->first->setPrev(aux);
        }
    }
    this->lenght += 1;
}

//Mejor caso: cuando la lista está vacía o el último nodo tiene el mismo valor e_.  
//Solo actualiza punteros o incrementa la cantidad del nodo final 
//                  T(n) ∈ O(1)

//Peor caso: cuando se debe crear un nodo nuevo al final.  
//La creación del nodo y la actualización de punteros son operaciones constantes 
//                  T(n) ∈ O(1)

//De manera general: T(n) ∈ O(1)
void CCL::push_back(Element e_, int q) {
    if (this->first == NULL)
    {
        this->first = new Node(e_);
        this->first->setNext(this->first);
        this->first->setPrev(this->first);
        this->first->setQuantity(q);
    }
    else
    {
        Node* tmp = this->first->getPrev();
        if (tmp->getVal() == e_)
        {
            tmp->addQuantity(q);
        }
        else
        {
            Node* aux = new Node(e_);
            aux->setPrev(tmp);
            tmp->setNext(aux);
            aux->setQuantity(q);
            aux->setNext(this->first);
            this->first->setPrev(aux);
        }
    }
    this->lenght += q;
}

//Mejor caso: cuando la lista está vacía o el primer nodo tiene el mismo valor e_.  
//Solo modifica cantidad o inicializa la lista, sin recorrer nada 
//                  T(n) ∈ O(1)

//Peor caso: cuando se debe crear un nuevo nodo y ubicarlo antes del primero.  
//La creación del nodo y la actualización de punteros son operaciones constantes 
//                  T(n) ∈ O(1)

//De manera general: T(n) ∈ O(1)
void CCL::push_front(Element e_, int q) {
    if (this->first == NULL)
    {
        this->first = new Node(e_);
        this->first->setNext(this->first);
        this->first->setPrev(this->first);
        this->first->setQuantity(q);
    }
    else
    {
        Node* tmp = this->first;
        if (tmp->getVal() == e_)
        {
            tmp->addQuantity(q);
        }
        else
        {
            Node* aux = new Node(e_);
            aux->setQuantity(q);
            aux->setPrev(tmp->getPrev());
            aux->getPrev()->setNext(aux);

            aux->setNext(tmp);
            tmp->setPrev(aux);
            
            this->first = aux;
        }
    }
    this->lenght += q;
}

// Mejor caso: cuando la lista está vacía o cuando i_ >= lenght y se inserta al final con el push_back 
//                  T(n) E O(1)

// Peor caso: cuando i_ está dentro del rango [0, lenght-1] y la posición está hacia el final de la lista. 
// Se recorre la estructura sumando quantities hasta ubicar el nodo correspondiente 
//                   T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
void CCL::insertElement(int i_, Element e_) {

    if (this->first == nullptr) {
        Node* n = new Node(e_);
        n->setNext(n);
        n->setPrev(n);
        this->first = n;
        this->lenght = 1;
    }
    else if (i_ >= this->lenght) {
        this->push_back(e_);
    }
    else {
        Node* tmp = this->first;
        int index = 0;

        while (index + tmp->getQuantity() <= i_) {
            index += tmp->getQuantity();
            tmp = tmp->getNext();
        }

        int posInNode = i_ - index;
        int q = tmp->getQuantity();

        if (tmp->getVal() == e_) {
            tmp->addQuantity(1);
            ++this->lenght;
        } 
        else if (posInNode == 0) {
            Node* prev = tmp->getPrev();
            if (prev->getVal() == e_) {
                prev->addQuantity(1);
            } else {
                Node* n = new Node(e_);
                n->setPrev(prev);
                n->setNext(tmp);
                prev->setNext(n);
                tmp->setPrev(n);
                if (tmp == this->first) {
                    this->first = n;
                }
            }
            ++this->lenght;
        }
        else {
            int left = posInNode;
            int rightC = q - posInNode;

            Node* next = tmp->getNext();
            tmp->setQuantity(left);

            Node* mid = new Node(e_);
            Node* right = new Node(tmp->getVal(), rightC);

            tmp->setNext(mid);
            mid->setPrev(tmp);

            mid->setNext(right);
            right->setPrev(mid);

            right->setNext(next);
            next->setPrev(right);

            ++this->lenght;
        }    
    }
}

// Mejor caso: cuando la lista está vacía (first == nullptr).
// Solo hace la validación inicial y no entra al ciclo 
//           T(n) E O(1)

// Peor caso: cuando la lista no está vacía.
// Llama a node_size() (que recorre todos los nodos) y luego el while también 
// recorre todos los nodos para eliminar las ocurrencias de e_ 
//           T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
void CCL::removeAllOcurrences(Element e_) {
    Node* cur = this->first;
    bool valid = true;

    if (cur == nullptr) {
        valid = false;
    }

    if (valid) {
        int total_nodes = this->node_size();
        int processed = 0;
        Node* new_first = this->first;

        while (processed < total_nodes && this->first != nullptr) {
            Node* next = cur->getNext();

            if (cur->getVal() == e_) {
                this->lenght -= cur->getQuantity();

                if (cur->getNext() == cur) {
                    delete cur;
                    this->first = nullptr;
                    new_first = nullptr;
                } else {
                    cur->getPrev()->setNext(cur->getNext());
                    cur->getNext()->setPrev(cur->getPrev());
                    if (cur == new_first) {
                        new_first = next;
                    }
                    delete cur;
                }
            }

            cur = next;
            processed++;
        }

        this->first = new_first;
    }
}

// Mejor caso: cuando la primera ocurrencia de e_ está en el primer nodo de la lista. 
// Se elimina o se disminuye la cantidad en la primera iteración del while
//              T(n) E O(1)
//
// Peor caso: cuando e_ no aparece en ningún nodo o está en el último nodo de la lista. 
// El while recorre todos los nodos una sola vez hasta dar la vuelta completa 
//              T(n) E O(n)
//
// De manera general se puede decir: T(n) E O(n)
void CCL::removeFirstOcurrence(Element e_) {
    Node* tmp = this->first;
    bool firstIt = true;
    bool erased = false;

    while ((firstIt || tmp != this->first) && !erased)
    {
        firstIt = false;

        if (tmp->getVal() == e_)
        {
            if (tmp->getQuantity() - 1 == 0)
            {
                tmp->getPrev()->setNext(tmp->getNext());
                tmp->getNext()->setPrev(tmp->getPrev());

                delete tmp;
            }
            else
            {
                tmp->subsQuantity(1);
            }

            this->lenght--;
            erased = true;
        }
        
        tmp = tmp->getNext();
    }
}

// Mejor caso: cuando el elemento e_ sí aparece en la lista.  
// Igual se debe recorrer toda la lista para eliminar sus ocurrencias 
//          T(n) E O(n)
//
// Peor caso: cuando e_ no aparece en ningún nodo, se recorre toda la lista completa sin
// eliminar nada, verificando cada nodo una vez 
//          T(n) E O(n)
//
// De manera general se puede decir: T(n) E O(n)
void CCL::removeAllOcurrence(Element e_) {
    Node* tmp = this->first->getNext();

    while (tmp != this->first)
    {
        if (tmp->getVal() == e_)
        {
            if (tmp->getNext() == tmp)
            {
                this->lenght = 0;
                this->first = nullptr;
                delete tmp;
            }
            else
            {
                this->lenght -= tmp->getQuantity();
                tmp->getNext()->setPrev(tmp->getPrev());
                tmp->getPrev()->setNext(tmp->getNext());
                Node* aux = tmp->getPrev();
                delete tmp;
                tmp = aux;
            }
        }
        tmp = tmp->getNext();
    }

    if (tmp->getVal() == e_)
    {

        if (tmp->getNext() == tmp)
        {
            this->lenght = 0;
            this->first = nullptr;
            delete tmp;
        }
        else
        {
           this->lenght -= tmp->getQuantity();
            tmp->getPrev()->setNext(tmp->getNext());
            tmp->getNext()->setPrev(tmp->getPrev());
            this->first = tmp->getNext();
            delete tmp; 
        }
    }
}

//Mejor caso: cuando la lista no está vacía y el índice i_ cae dentro del primer bloque 
//Se elimina el primer nodo sin necesidad de recorrer la lista 
//          T(n) E O(1)

//Peor caso: cuando el índice i_ es válido pero corresponde a un bloque que está hacia el final de la 
//lista. El while recorre bloque por bloque acumulando quantities hasta ubicar el nodo a eliminar, 
//por lo que en el peor caso pasa por todos los nodos 
//          T(n) E O(n)

//De manera general se puede decir: T(n) E O(n)
void CCL::removeBlockPosition(int i_) {
    if (this->first == NULL || i_ < 0 || i_ >= this->lenght)
    {
        return;
    }

    Node* tmp = this->first;
    int q = tmp->getQuantity();

    while (i_ >= q)
    {
        tmp = tmp->getNext();
        q += tmp->getQuantity();
    }
    this->lenght -= tmp->getQuantity();

    if (tmp->getNext() == tmp)
    {
        delete tmp;
        this->first = NULL;
    }
    else
    {
        Node* aux = tmp->getPrev();
        Node* nxt = tmp->getNext();
        nxt->setPrev(aux);
        aux->setNext(nxt);

        if (tmp == this->first)
        {
            this->first = nxt;
        }

        delete tmp;
    }
}

//De manera general se puede decir: T(n) E O(1)
void CCL::push_back_node(Node* _n_) {
    Node* tmp = this->first->getPrev();

    _n_->setNext(tmp->getNext());
    _n_->setPrev(tmp);
    tmp->getNext()->setPrev(_n_);
    tmp->setNext(_n_);
    this->lenght += _n_->getQuantity();
}

//Mejor caso: cuando la CCL actual está vacía 
//      T(n) E O(1)

//Peor caso: cuando ambas listas no están vacías.  
//Se llaman node_size() sobre las dos CCL donde se recorren todos sus nodos
//y luego los ciclos while fusionan recorriendo todos los nodos de los 2
//      T(n) E O(n + n)

//De manera general se puede decir: T(n) E O(n)
void CCL::getLexicographicFusion(CCL _c_) {
    if (this->first == NULL) {
        this->first = _c_.first;
        this->lenght = _c_.lenght;
    } else {
        int left_remaining = this->node_size();
        int right_remaining = _c_.node_size();

        int i = 0, j = 0;

        Node* left = this->first;
        Node* right = _c_.first;
        Node* aux;
        Node* rightFirst = _c_.first;
        
        while (i < left_remaining && j < right_remaining) {

            if (left->getVal() < right->getVal()) {
                ++i;
                left = left->getNext();
            } 
            else if (left->getVal() == right->getVal()) {

                aux = right->getNext();
                right->getPrev()->setNext(aux);
                aux->setPrev(right->getPrev());
                left->addQuantity(right->getQuantity());
                this->lenght += right->getQuantity();

                ++i;
                ++j;

                left = left->getNext();
                right = aux;
            } 
            else {

                aux = right->getNext();
                right->getPrev()->setNext(aux);
                aux->setPrev(right->getPrev());
                left->getPrev()->setNext(right);
                right->setNext(left);
                right->setPrev(left->getPrev());
                left->setPrev(right);

                this->lenght += right->getQuantity();
                right = aux;

                ++left_remaining;
                ++j;
            }
        }
        
        while (j < right_remaining) {
            aux = right->getNext();
            right->getPrev()->setNext(aux);
            aux->setPrev(right->getPrev());
            push_back_node(right);
            ++j;
            right = aux;
        }

        this->first = rightFirst;
    }
}

//Mejor caso: cuando la lista está vacía  
//      T(n) E O(1)

//Peor caso: cuando la lista no está vacía.  
//Recorre todos los nodos y por cada nodo, inserta en la lista de salida de elementos como su quantity
//insertando n elementos 

//De manera general se puede decir: T(n) E O(n)
list<Element> CCL::expand() {
    list<Element> ans;
    Node* tmp = this->first;
    bool first_time = true;
    bool valid = true;

    if (tmp == nullptr) {
        valid = false;
    }

    if (valid) {
        while (first_time || tmp != this->first) {
            first_time = false;
            int q = tmp->getQuantity();
            int i = 0;
            while (i < q) {
                ans.push_back(tmp->getVal());
                i++;
            }
            tmp = tmp->getNext();
        }
    }

    return ans;
}

//Mejor caso: cuando el índice es inválido o cuando i == 0.  
//si i == 0, se toma directamente el primer valor
//      T(n) E O(1)

//Peor caso: cuando el índice i es válido y corresponde a una posición hacia el final de la lista.  
//El while recorre nodo por nodo y el for interno recorre las quantities hasta llegar a la posición de i
//      T(n) E O(n)

//De manera general se puede decir: T(n) E O(n)
Element CCL::operator[](int i) const {
    Node* tmp = this->first;
    Element ans{};

    if (!(i < 0 || i >= this->lenght || this->first == NULL))
    {
        if (i == 0)
        {
            ans = tmp->getVal();
        }
        else
        {
            bool first_loop = true, found = false;

            i++;

            while ((tmp != this->first || first_loop) && !found)
            {
                first_loop = false;

                for (int j = 0; j < tmp->getQuantity() && i > 0; j++)
                {
                    --i;
                }

                if (i == 0)
                {
                    ans = tmp->getVal();
                    found = true;
                }
                tmp = tmp->getNext();
            }
        }
    }
    return ans;
}

//Mejor caso: aunque encuentre la primera ocurrencia de _e_ de inmediato, igual debe recorrer 
//toda la lista  
//      T(n) E O(n)

//Peor caso: cuando _e_ no aparece en ningún nodo. También recorre todos los nodos de la lista 
//verificando uno por uno
//      T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
void CCL::modifyAllOcurrences(Element _e, Element _aux) {
    Node* tmp = this->first;
    bool firstIt = true;

    while (firstIt || tmp != this->first)
    {
        firstIt = false;

        if (tmp->getVal() == _e)
        {
            tmp->setVal(_aux);
        }

        tmp = tmp->getNext();
    }
    
}

// Mejor caso: cuando el lenght de ambas CCL son diferentes.  
// Se detecta en la primera comparación y retorna sin recorrer ningún nodo 
//          T(n) E O(1)

// Peor caso: cuando las longitudes son iguales.  
// Se recorre nodo por nodo en ambas listas verificando valor y quantity 
//          T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
bool CCL::operator==(const CCL& _c_) const {
    bool ans = true;
    if (this->lenght != _c_.lenght)
    {
        ans = false;
    }
    else
    {
        bool first_loop = true;
        Node* tmp = this->first;
        Node* aux = _c_.first;
        while ((tmp != this->first || first_loop) && ans && (aux != _c_.first || first_loop))  
        {
            first_loop = false;
            if (tmp->getVal() != aux->getVal() || tmp->getQuantity() != aux->getQuantity())
            {
                ans = false;
            }
            tmp = tmp->getNext();
            aux = aux->getNext();
        }

        if (tmp != this->first || aux != _c_.first)
        {
            ans = false;
        }
    }
    return ans;
    
}

//Mejor caso: cuando la primera lista está vacía o cuando la segunda lista está vacía   
//La comparación termina de inmediato sin recorrer nada 
//          T(n) E O(1)

//Peor caso: cuando ambas listas NO están vacías.  
//Se recorre completamente cada lista para sumar la quantity de cada nodo.  
//          T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
bool CCL::operator<(const CCL &_c_) const {
    bool ans;
    if (this->first == NULL)
    {
        ans = true;
    }
    else if (_c_.first == NULL)
    {
        ans = false;
    }
    else
    {
        Node* tmp = this->first;
        bool first = true;
        int thisObj = 0, othr = 0;

        while (tmp != this->first || first)
        {
            first = false;

            thisObj+= tmp->getVal() * tmp->getQuantity();

            tmp = tmp->getNext();
        }

        tmp = _c_.first;
        first = true;
        
        while (tmp != _c_.first || first)
        {
            first = false;

            othr += tmp->getVal() * tmp->getQuantity();

            tmp = tmp->getNext();
        }
        ans = thisObj < othr;
    }
    return ans;
}

//Mejor caso: cuando la lista actual está vacía.  
//Se copia la otra CCL y luego se fusiona directamente sin necesidad de recorrer la primera
//         T(n) E O(n)

//Peor caso: cuando ambas listas tienen elementos.  
//Se crean dos copias completas y luego la funcion de getLexicographicFusion realiza una
//fusión lineal.  
//         T(n) E O(n)

// De manera general se puede decir: T(n) E O(n)
CCL CCL::operator+(CCL &other) const {
    CCL ans(*this);
    CCL othr_(other);
    ans.getLexicographicFusion(othr_);

    return ans;
}


//Cuando el vector está completamente desordenado o ordenado.  
//el sort sigue siendo una operacion con coste de O(n log n) 
//          T(n) E O(n log n)

// De manera general se puede decir: T(n) E O(n log n)
void CCL::sortVectorCCL(vector<CCL> &v_) {
    sort(v_.begin(), v_.end());
}