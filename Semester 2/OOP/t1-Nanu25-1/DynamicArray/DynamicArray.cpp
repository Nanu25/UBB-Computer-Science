#include <stdexcept>
#include "DynamicArray.h"

DynamicArray::DynamicArray(int cap): capacity(cap), length(0) {
    this->elems = new TElement[this->capacity];
}

DynamicArray::~DynamicArray() {
    delete[] this->elems;
}

int DynamicArray::getCapacity() {
    return this->capacity;
}

int DynamicArray::getLength() {
    return this->length;
}

TElement DynamicArray::getElem(int position) {
    if (position < 0 || position >= getLength()) {
        throw std::out_of_range("Index out of bounds");
    }
    return elems[position];
}

void DynamicArray::setElement(int position, TElement x) {
    if (position < 0 || position >= getLength()) {
        throw std::out_of_range("Index out of bounds");
    }
    elems[position] = x;
}

void DynamicArray::resize() {
    int new_capacity = 2 * capacity;
    TElement *new_elems = new TElement[new_capacity];

    for (int i = 0; i < this->length; i++) {
        new_elems[i] = elems[i];
    }

    delete[] elems;
    elems = new_elems;
    capacity = new_capacity;
}

void DynamicArray::add(TElement x) {
    if(this->length == this->capacity)
        resize();

    this->elems[this->length++] = x;
}

void DynamicArray::remove(int position) {
    if(position < 0 || position >= this->length)
        throw std::out_of_range("Index out of bounds");

    for(int i = position; i < this->length - 1; i++)
        this->elems[i] = this->elems[i + 1];
    this->length--;
}

void DynamicArray::update(int position, TElement x) {
    this->elems[position] = x;
}

void DynamicArray::setLength(int new_len) {
    this->length = new_len;
}
