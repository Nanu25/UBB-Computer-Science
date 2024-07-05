#pragma once

#include "Movie.h"
#include <stdexcept>

typedef Movie TElement;

template <typename T>
class DynamicArray {
private:
    int length, capacity;
    TElement *elems;
public:
    DynamicArray(int cap = 10);
    ~DynamicArray();

    //Getters
    int getCapacity();
    int getLength();
    TElement getElem(int position);

    //Setters
    void setElement(int position, Movie x);
    void setLength(int new_len);

    void add(TElement x);
    void remove(int position);
    void update(int position, TElement x);
    void resize();
};

template <typename T>
DynamicArray<T>::DynamicArray(int cap): capacity(cap), length(0) {
    this->elems = new TElement[this->capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->elems;
}

template <typename T>
int DynamicArray<T>::getCapacity() {
    return this->capacity;
}

template <typename T>
int DynamicArray<T>::getLength() {
    return this->length;
}

template <typename T>
TElement DynamicArray <T>::getElem(int position) {
    if (position < 0 || position >= getLength()) {
        throw std::out_of_range("Index out of bounds");
    }
    return elems[position];
}

template <typename T>
void DynamicArray<T>::setElement(int position, TElement x) {
    if (position < 0 || position >= getLength()) {
        throw std::out_of_range("Index out of bounds");
    }
    elems[position] = x;
}

template <typename T>
void DynamicArray<T>::resize() {
    int new_capacity = 2 * capacity;
    TElement *new_elems = new TElement[new_capacity];

    for (int i = 0; i < this->length; i++) {
        new_elems[i] = elems[i];
    }

    delete[] elems;
    elems = new_elems;
    capacity = new_capacity;
}

template <typename T>
void DynamicArray<T>::add(TElement x) {
    if(this->length == this->capacity)
        resize();

    this->elems[this->length++] = x;
}

template <typename T>
void DynamicArray<T>::remove(int position) {
    if(position < 0 || position >= this->length)
        throw std::out_of_range("Index out of bounds");

    for(int i = position; i < this->length - 1; i++)
        this->elems[i] = this->elems[i + 1];
    this->length--;
}

template <typename T>
void DynamicArray<T>::update(int position, TElement x) {
    this->elems[position] = x;
}

template <typename T>
void DynamicArray<T>::setLength(int new_len) {
    this->length = new_len;
}
