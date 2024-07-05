#include "Set.h"
#include "SetITerator.h"

///BC = WC = TC = Theta(1)
Set::Set() {
    this->capacity = 1;
    this->setSize = 0;
    this->elements = new TElem[1];
}

///BC = Theta(1)
///WC = Theta(setSize)
///TC =  O(1), amortized
void Set::resize() {
    int newCapacity = this->capacity * 2;
    TElem* new_elems = new TElem[newCapacity];

    for(int i = 0; i < this->setSize; i++)
        new_elems[i] = this->elements[i];

    delete[] this->elements;
    this->elements = new_elems;
    this->capacity = newCapacity;

}

///BC = Theta(1)
///WC = Theta(setSize)
///TC = O(setSize)
bool Set::add(TElem elem) {

    ///try to find another appereance of elem in my array
    int index = 0;
    while (index < this->setSize && this->elements[index] != elem) {
        index++;
    }

    if(index != this->setSize)
        return false;

    if(this->setSize == this->capacity)
        resize();

    this->elements[index] = elem;
    this->setSize++;
	return true;
}

///BC = Theta(1)
///WC = Theta(setSize)
///TC = O(setSize)
bool Set::remove(TElem elem) {

    int index = 0;
    while(index < this->setSize && this->elements[index] != elem) {
        index++;
    }

    if(index == this->setSize)
        return false;

    this->elements[index] = this->elements[this->setSize - 1];
    this->setSize--;

    return true;
}

///BC = Theta(1)
///WC = Theta(setSize)
///TC = O(setSize)
bool Set::search(TElem elem) const {
    int index = 0;
    while(index < this->setSize && this->elements[index] != elem) {
        index++;
    }

    return index != this->setSize;
}

///BC = WC = TC = Theta(1)
int Set::size() const {
    return this->setSize;
}

///BC = WC = TC = Theta(1)
bool Set::isEmpty() const {
    return this->setSize == 0;
}

///BC = WC = TC = Theta(1)
Set::~Set() {
    delete[] this->elements;
}

///BC = WC = TC = Theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}

/// BC = Theta(n)
/// WC = O(n^2)
/// TC = O(n^2)
void Set::intersection(const Set &s) {
    int index = 0;
    while(index < this->setSize) {
        if(s.search(this->elements[index]) == false) {   //if the current element don't appear in set s i will delete it.
            this->remove(this->elements[index]);
        }else index++;
    }
}


