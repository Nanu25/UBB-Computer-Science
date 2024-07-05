#include <stdexcept>
#include "Repository.h"

void Repository::Add(Movie x) {
    if(Find(x.getTitle()) != -1)
        throw std::runtime_error("This film already exists.");

    this->repo.add(x);
}


void Repository::Delete(std::string title) {
    int position = Find(title);
    if(position == -1)
        throw std::runtime_error("This movie doesn't exist");

    //Delete the movie at the position I found it.
    for(int i = position; i < this->repo.getLength() - 1; i++)
        this->repo.setElement(i, this->repo.getElem(i + 1));
    this->repo.setLength(this->repo.getLength() - 1);
}

int Repository::Find(std::string title) {
    for(int i = 0; i < this->repo.getLength(); i++)
        if(title == this->repo.getElem(i).getTitle())
            return i;
    return -1;
}

Movie Repository::getElement(int position) {
    return this->repo.getElem(position);
}

int Repository::getRepoLength() {
    return this->repo.getLength();
}

void Repository::Update(std::string title, Movie x) {
    int position = Find(title);
    if(position == -1)
        throw std::runtime_error("This movie doesn't exist"); // Corrected throw statement
    this->repo.setElement(position, x);
}

Repository::Repository(){
}

void Repository::setElem(int position, Movie x) {
    this->repo.setElement(position, x);
}
