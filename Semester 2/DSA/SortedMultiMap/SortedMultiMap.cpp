#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//BC = WC = TC = Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
    this->r = r;
    this->length = 0;
}

//BC : Theta(1)
//WC : Theta(n), n is the size of the map;
//TC : O(n);
void SortedMultiMap::add(TKey c, TValue v) {
    if (this->elems.size == this->elems.cap && this->elems.firstempty == -1){
        this->elems.cap *= 2;
        auto *aux = new SLLNode [this->elems.cap];
        for (int i = 0; i < this->elems.size; ++i)
            aux[i] = this->elems.list[i];
        delete[] this->elems.list;
        this->elems.list = aux;
    }
    if (this->elems.firstempty == -1){
        this->elems.firstempty = this->elems.size;
        this->elems.list[this->elems.firstempty] = SLLNode({-1, -1}, -1);
        ++this->elems.size;
    }

    if (this->length == 0){
        int copy_empty = this->elems.firstempty;
        this->elems.firstempty = this->elems.list[this->elems.firstempty].next;
        this->elems.list[copy_empty] = SLLNode({c, v}, -1);
        this->elems.head = copy_empty;
        ++this->length;
        return;
    }

    int copy_empty = this->elems.firstempty;
    this->elems.firstempty = this->elems.list[this->elems.firstempty].next;
    if (r(c, this->elems.list[this->elems.head].info.first)){  //place it in first position
        this->elems.list[copy_empty] = SLLNode({c, v}, this->elems.head);
        this->elems.head = copy_empty;
        ++this->length;
        return;
    }
    int after = this->elems.head;
    for (int node = this->elems.head; node != -1; node = this->elems.list[node].next){
        if (r(this->elems.list[node].info.first, c) && this->elems.list[node].info.first != c)
            after = node;
        else break;
    }

    this->elems.list[copy_empty] = SLLNode({c, v}, this->elems.list[after].next);
    this->elems.list[after].next = copy_empty;
    ++this->length;
}

//BC : Theta(1)
//WC : Theta(n), n is the size of the map;;
//TC : O(n);
vector<TValue> SortedMultiMap::search(TKey c) const {
    //TODO - Implementation
    vector <TValue> aux;
    int node = this->elems.head;
    while(node != -1) {
        if(this->elems.list[node].info.first == c)
            aux.push_back(this->elems.list[node].info.second);
        node = this->elems.list[node].next;
    }
    return aux;
}

//BC : Theta(1)
//WC : Theta(n), n is the size of the map;;
//TC : O(n);
bool SortedMultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    //First position
    int node = this->elems.head;
    if(this->elems.list[node].info == make_pair(c, v)) {
        int headcopy = this->elems.list[this->elems.head].next;
        this->elems.list[node].next = this->elems.firstempty;
        this->elems.firstempty = this->elems.head;
        this->elems.head = headcopy;
        this->length--;
        return true;
    }

    int prev_node = 0;
    while(node != -1) {
        if(this->elems.list[node].info == make_pair(c, v)) {
            ///Delete the element from position node.
            this->elems.list[prev_node].next = this->elems.list[node].next;
            this->elems.list[node].next = -1;
            this->length--;
            this->elems.firstempty = node;
            return true;
        }
        prev_node = node;
        node = this->elems.list[node].next;
    }
    return false;
}

//BC = WC = TC = Theta(1)
int SortedMultiMap::size() const {
    //TODO - Implementation
    return this->length;
}

//BC = WC = TC = Theta(1)
bool SortedMultiMap::isEmpty() const {
    //TODO - Implementation
    return this->length == 0;
}

//BC = WC = TC = Theta(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

//BC = WC = TC = Theta(1)
SortedMultiMap::~SortedMultiMap() {
    //TODO - Implementation
    delete[] this->elems.list;
}

void SortedMultiMap::filter(Condition cond) {
    SortedMultiMap smm{r};
    SMMIterator it = this->iterator();
    while(it.valid()) {
        if(cond(it.getCurrent().second) == 1)
            smm.add(it.getCurrent().first, it.getCurrent().second);
        it.next();
    }

    it.first();
    int prevk = it.getCurrent().first;
    int prevV = it.getCurrent().second;
    while (it.valid()) {
        it.next();

        remove(prevk, prevV);
        if(it.valid()) {
            prevk = it.getCurrent().first;
            prevV = it.getCurrent().second;
        }
    }


    SMMIterator smit = smm.iterator();
    while (smit.valid()) {
        this->add(smit.getCurrent().first, smit.getCurrent().second);
        smit.next();
    }
}

//BC = WC = TC = Theta(1)
SortedMultiMap::SLL::SLL() {
    this->cap = 1;
    this->size = 1;
    this->list = new SLLNode[this->cap];
    this->list[0] = SLLNode({-1, -1}, -1);
    this->firstempty = 0;
    this->head = -1;
}

//BC = WC = TC = Theta(1)
SortedMultiMap::SLLNode::SLLNode(): info{-1, -1}, next{0} {
}

//BC = WC = TC = Theta(1)
SortedMultiMap::SLLNode::SLLNode(TElem info, int next) : info{std::move(info)}, next{next} {
}

