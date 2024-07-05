#pragma once

#include "../DynamicArray/DynamicArray.h"

class Repository {
private:
    DynamicArray repo{1};
public:
    Repository();
    int Add(TElement x);
    int Find(std::string name);
    int getLen();
    int Remove(std::string name);

    Domain getElement(int position);
};


