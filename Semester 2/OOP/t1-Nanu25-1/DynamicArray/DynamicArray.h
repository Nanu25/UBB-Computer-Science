#pragma once

#include "../Domain/Domain.h"

typedef Domain TElement;

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
    void setElement(int position, TElement x);
    void setLength(int new_len);

    void add(TElement x);
    void remove(int position);
    void update(int position, TElement x);
    void resize();
};

