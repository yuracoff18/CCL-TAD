/*

    Yura Hernandez Hernandez
    Juan José Lopez
    28/11/25

    Compact Chan List
    Proyecto

*/

#include <iostream>
#include <vector>
#include <cctype>
#include <list>

using namespace std;

// Clases

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

class CCL
{
private:
    Node* first;
    int lenght;
public:
    // Constructores
    CCL(); // Hecho
    CCL(std::vector<Element> v_); // Hecho

    // Destructor
    ~CCL(); // Hecho

    // Analizadores
    int getConsecutiveOcurrences(std::vector<Element> &v_); // Hecho
    void push_back(Element e_);


    static void sortVectorCCL(vector<CCL> &v_);
};

CCL::CCL() {
    this->first = NULL;
    this->lenght = 0;
}

CCL::CCL(std::vector<Element> v_) {
    this->first = NULL;
    this->lenght = 0;

    for (size_t i = 0; i < v_.size(); i++)
    {
        this->push_back(v_[i]);
    }
}

CCL::~CCL() = default;

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

// fin clases

vector<char> stringToVectorChar(string &s) {
    vector<char> ans;
    ans.push_back('-');
    for (int i = 0; i < s.size(); i++)
    {
        if (isalpha(s[i]))
        {
            ans.push_back(tolower(s[i]));
        }
        else
        {
            ans.push_back('-');
        }
        
    }
    ans.push_back('-');
    return ans;
}

void printVectorInt(vector<int> &in) {
    for (int i = 0; i < in.size(); i++)
    {
        printf("%d ", in[i]);
    }
    printf("\n");
}

int main()
{
    
    int k, e;

    while (cin >> k >> e)
    {
        vector<vector<char>> strange;
        vector<CCL> excuses;
        vector<string> originalExcuses;

        string aux;
        for (int i = 0; i < k; i++)
        {
            cin >> aux;
            strange.push_back(stringToVectorChar(aux));
        }

        cin.ignore();

        for (int i = 0; i < e; i++)
        {
            getline(cin , aux);
            excuses.push_back(CCL(stringToVectorChar(aux)));
            originalExcuses.push_back(aux);
        }

        vector<int> suspiciusEach(excuses.size(), 0);
        
        int max = 0;
        for (int i = 0; i < excuses.size(); i++)
        {
            for (int j = 0; j < strange.size(); j++)
            {
                suspiciusEach[i] += excuses[i].getConsecutiveOcurrences(strange[j]);
            }

            if (suspiciusEach[i] > max)
                max = suspiciusEach[i];
        }

        for (int i = 0; i < excuses.size(); i++)
        {
            if (suspiciusEach[i] == max)
            {
                printf("%s\n", originalExcuses[i].c_str());
            }
        }
        printf("\n");
    }
    
    return 0;
}
