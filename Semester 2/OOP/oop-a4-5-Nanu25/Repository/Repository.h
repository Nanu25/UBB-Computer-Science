#pragma once

#include "../DynamicArray/DynamicArray.h"
#include "../Domain/Movie.h"

class Repository {

private:
    DynamicArray <TElement> repo;

public:
    Repository();
    void Add(Movie x);
    void Delete(std::string title);
    void Update(std::string title, Movie x);
    int Find(std::string title);

    Movie getElement(int position);
    int getRepoLength();

    void setElem(int position, Movie x);
};


