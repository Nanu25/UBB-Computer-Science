#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;


//BC = WC = TC = Theta(1)
Bag::Bag() {
	//TODO - Implementation
    this->m = 10;
    this->htable = new Node*[m];
    this->sizeH = 0;
    for(int i = 0; i < this->m; i++)
        this->htable[i] = nullptr;
}

//BC = WC = TC = Theta(1)
void Bag::add(TElem elem) {
	//TODO - Implementation
    if ((float)this->sizeH / (float)this->m >= ALPHA) {
        resize(2 * m);
    }
    //We add it on the first position of the corresponding list.
    int key = this->h(elem);
    auto newNode = new Node;
    newNode->next = this->htable[key];
    newNode->key = elem;
    this->htable[key] = newNode;
    this->sizeH++;
}

//BC: Theta(1),
//WC: Theta(M), where M is the maximum number of elements associated to a key
//Total: O(M)
bool Bag::remove(TElem elem) {
	//TODO - Implementation
    int key = this->h(elem);
    auto current = this->htable[key];
    Node* prev = nullptr;
    bool ok = 0;
    while(current != NULL) {
        if(current->key == elem) {
            if(prev == nullptr)
                this->htable[key] = current->next;
            else prev->next = current->next;

            delete current;
            ok = 1;
            this->sizeH--;
            break;
        }
        prev = current;
        current = current->next;
    }
    return ok;
}

//BC : Theta(1)
//WC : Theta(m), m is the size of distinct elements associated to a key
//TC : O(m);
bool Bag::search(TElem elem) const {
	//TODO - Implementation
	int key = this->h(elem);
    auto current = this->htable[key];
    bool ok = 0;
    while(current != NULL) {
        if(current->key == elem) {
            ok = 1;
            break;
        }
        current = current->next;
    }
    return ok;
}

//BC : Theta(m)
//WC : Theta(m), m is the size of distinct elements associated to a key
//TC : Theta(m);
int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
    int key = this->h(elem);
    auto current = this->htable[key];
    int ap = 0;
    while(current != NULL) {
        if(current->key == elem) {
            ap++;
        }
        current = current->next;
    }
    return ap;
}

//BC = WC = TC = Theta(1)
int Bag::size() const {
	//TODO - Implementation
	return this->sizeH;
}

//BC = WC = TC = Theta(1)
bool Bag::isEmpty() const {
	//TODO - Implementation
	return this->sizeH == 0;
}

//BC = WC = TC = Theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

//BC = WC = TC = Theta(hsize)
Bag::~Bag() {
	//TODO - Implementation
    for (int i = 0; i < this->m; ++i) {
        auto current = this->htable[i];
        while (current != nullptr) {
            auto prev = current;
            current = current->next;
            delete prev;
        }
    }
    delete[] this->htable;
}

//BC = WC = TC = Theta(1)
int Bag::h(TElem elem) const {
    return abs(elem % this->m);
}

//BC: Theta(M)
//WC: Theta(M), where M is the maximum number of distinct elements associated to a key
//TC: Theta(M)
void Bag::resize(int newcap) {
    Node** newhtable = new Node*[newcap];
    for(int i = 0; i < newcap; i++)
        newhtable[i] = nullptr;

    int lastm = this->m;
    this->m = newcap;
    for(int i = 0; i < lastm; i++) {
        auto current = this->htable[i];
        //Rehash
        while(current != NULL) {
            auto prev = current;
            int key = this->h(current->key);
            Node* newNode = new Node;
            newNode->next = newhtable[key];
            newNode->key = current->key;
            newhtable[key] = newNode;
            current = current->next;
            delete prev;
        }
    }

    delete[] this->htable;
    this->htable = newhtable;
}

bool findElem(std::vector<int> a, int e) {
    for(auto elem : a)
        if(elem == e)
            return 1;
    return 0;
}

//TC = O(sizeh* m)
vector<int> Bag::histogram() {
    std::vector <int> fr;
    std::vector <int> used;

    for(int i = 0; i <= this->sizeH; i++)
        fr.push_back(0);

    BagIterator it = this->iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();

        if(findElem(used, e) == 0) {
            //find the fr for e
            int ap = this->nrOccurrences(e);
            fr[ap]++;
            used.push_back(e);
        }

        it.next();
    }

    while(fr[fr.size() - 1] == 0)
        fr.pop_back();

    return fr;
}

