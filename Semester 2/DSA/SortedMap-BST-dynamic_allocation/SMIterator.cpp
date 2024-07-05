#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//TODO - Implementation
    BSTNode* start = this->map.root;
    this->current = 0;
    this->inOrderRecursive(start);
}

//Theta(1)
void SMIterator::first(){
	//TODO - Implementation
    this->current = 0;
}

//Theta(1)
void SMIterator::next(){
	//TODO - Implementation
    if(!valid())
        throw exception();
    this->current++;
}

//Theta(1)
bool SMIterator::valid() const{
	//TODO - Implementation
    return (this->current < this->stack.getNrElements());
}

//Theta(1)
TElem SMIterator::getCurrent() const{
	//TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    return this->stack[this->current];
}

//Theta(nrElements);
void SMIterator::inOrderRecursive(BSTNode *start) {
    if(start != nullptr) {
        inOrderRecursive(start->left);
        this->stack.push(start);
        inOrderRecursive(start->right);
    }
}

//Theta(1)
Stack::Stack(): nrElements{0}, capacity{10} {
    this->elements = new BSTNode*[capacity];
}

//Theta(1)
int Stack::getNrElements() const {
    return this->nrElements;
}

//Theta(1)
void Stack::push(BSTNode *element) {
    if (this->nrElements == this->capacity)
        this->resize();
    this->elements[this->nrElements] = element;
    this->nrElements++;
}

//Theta(nrElements)
void Stack::resize() {
    auto** newElements = new BSTNode*[this->capacity * 2];
    int index;
    for (index = 0; index < this->nrElements; ++index) {
        newElements[index] = this->elements[index];
    }
    this->capacity = this->capacity * 2;
    delete [] this->elements;
    this->elements = newElements;
}

//Theta(1)
TElem Stack::operator[](int position) const {
    return this->elements[position]->info;
}

//Theta(1)
Stack::~Stack() {
    delete [] this->elements;
}


