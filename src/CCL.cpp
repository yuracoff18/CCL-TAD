#include "CCL.h"

// Constructores

CCL::CCL() {
    this->first = NULL;
    this->lenght = 0;
}

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

CCL::CCL(std::vector<Element> v_) {
    this->first = NULL;
    this->lenght = 0;

    for (size_t i = 0; i < v_.size(); i++)
    {
        this->push_back(v_[i]);
    }
}

// Destructor

CCL::~CCL() = default;

// Analizadores

int CCL::size() {
    return this->lenght;
}

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
                std::size_t k = 0;
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
                    ans = (i) + loked;
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

int CCL::searchElement(Element &e_) {
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


void CCL::removeFirstOcurrence(Element e_) {
    Node* tmp = this->first;

    if (tmp->getVal() == e_)
    {
        if (tmp->getQuantity() == 1)
        {
            if (tmp->getNext() == tmp)
            {
                this->first = NULL;
                
            }
            else
            {
                tmp->getPrev()->setNext(tmp->getNext());
                tmp->getNext()->setPrev(tmp->getPrev());
                Node* aux = tmp->getPrev();
                delete tmp;
                this->first = aux->getNext();
            }
            --this->lenght;
        }
        else
        {
            tmp->subsQuantity(1);
            --this->lenght;
        }
    }
    else
    {
        tmp = tmp->getNext();
        bool deleted = false;
        while (tmp != this->first && !deleted)
        {
            if (tmp->getVal() == e_)
            {
                if (tmp->getQuantity() == 1)
                {
                    tmp->getNext()->setPrev(tmp->getPrev());
                    tmp->getPrev()->setNext(tmp->getNext());
                    delete tmp;
                }
                else
                {
                    tmp->subsQuantity(1);
                }
                --this->lenght;
                deleted = true;
            }
            else
            {
                tmp = tmp->getNext();
            }
        }
    }
}

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

void CCL::removeBlockPosition(int i_) {
    Node* tmp = this->first;
    int q = 0;

    while (i_ > q)
    {
        q += tmp->getQuantity();
        tmp = tmp->getNext();
    }

    this->lenght -= tmp->getQuantity();

    Node* aux = tmp->getPrev();
    tmp->getNext()->setPrev(aux);
    aux->setNext(tmp->getNext());
    delete tmp;
}

void CCL::push_back_node(Node* _n_) {
    Node* tmp = this->first->getPrev();

    _n_->setNext(tmp->getNext());
    _n_->setPrev(tmp);
    tmp->getNext()->setPrev(_n_);
    tmp->setNext(_n_);
    this->lenght += _n_->getQuantity();
}


void CCL::getLexicographicFusion(CCL _c_) {

    if (this->first == NULL)
    {
        this->first = _c_.first;
        this->lenght = _c_.lenght;
    }
    else
    {
        int left_remaining = this->node_size(); 
        int right_remaining = _c_.node_size();
        int i = 0, j = 0;
        Node* left = this->first;
        Node* right = _c_.first;
        Node* aux;
        
        
        while (i < left_remaining && j < right_remaining)
        {

            if (left->getVal() < right->getVal())
            {
                ++i;
                left = left->getNext();
            }
            else if (left->getVal() == right->getVal())
            {
                aux = right->getNext();
                right->getPrev()->setNext(aux);
                aux->setPrev(right->getPrev());



                left->addQuantity(right->getQuantity());
                this->lenght += right->getQuantity();
                delete right;
                ++i;
                ++j;
                left = left->getNext();
                right = aux;
                
            }
            else
            {
                
                aux = right->getNext();
                right->getPrev()->setNext(aux);
                aux->setPrev(right->getPrev());

                left->getPrev()->setNext(right);
                right->setNext(left);
                right->setPrev(left->getPrev());
                left->setPrev(right);

                if (left == this->first)
                {
                    this->first = right;
                }
                
                this->lenght += right->getQuantity();
                right = aux;
                ++left_remaining;
                ++j;
            }
        }
        
        while (j < right_remaining)
        {
            aux = right->getNext();
            right->getPrev()->setNext(aux);
            aux->setPrev(right->getPrev());

            push_back_node(right);

            ++j;
            right = aux;
        }
    }
}



List CCL::expand() {
    List ans;
    Node* tmp = this->first;

    while (tmp->getNext() != this->first)
    {
        for (int i = 0; i < tmp->getQuantity(); i++)
        {
            ans.push_back(tmp->getVal());
        }
        tmp = tmp->getNext();
    }
    
    for (int i = 0; i < tmp->getQuantity(); i++)
    {
        ans.push_back(tmp->getVal());
    }

    return ans;
}


Element CCL::operator[](int i) const{
    Node* tmp = this->first;
    Element ans;
    if (!(i < 0 || i > this->lenght || this->first == NULL))
    {
        if (i == 0)
        {
            ans = tmp->getVal();
        }
        else
        {
            bool first_loop = true, found = false;
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

CCL CCL::operator+(CCL &other) const {
    CCL ans(*this);
    CCL othr_(other);
    ans.getLexicographicFusion(othr_);

    return ans;
}

void CCL::sortVectorCCL(vector<CCL> &v_) {
    sort(v_.begin(), v_.end());
}