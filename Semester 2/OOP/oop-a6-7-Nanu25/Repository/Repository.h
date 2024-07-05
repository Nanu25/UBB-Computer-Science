#pragma once

#include "../DynamicArray/DynamicArray.h"
#include "../Domain/Movie.h"
#include <vector>
#include <fstream>
#include <iostream>

typedef Movie TElement;

class Repository {

private:
    std::vector<TElement> repo;

public:

    virtual void Add(Movie x);

    virtual void Delete(std::string title);

    virtual void Update(std::string title, Movie x);

    virtual std::vector<TElement> &getRepo();

    virtual Movie getElement(int position);

    virtual int getRepoLength();

    virtual void setElem(int position, Movie x);

    virtual void save_data_to_file();

    virtual void readMoviesFromFile(std::string filename);

};

