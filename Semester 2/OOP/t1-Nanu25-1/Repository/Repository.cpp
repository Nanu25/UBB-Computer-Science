

#include "Repository.h"

Repository::Repository() {

}

int Repository::Add(TElement x) {
    if(Find(x.getName()) != -1)
        return -1;

    this->repo.add(x);
    return 1;
}

int Repository::Find(std::string name) {
    for(int i = 0; i < this->repo.getLength(); i++)
        if(name == this->repo.getElem(i).getName())
            return i;
    return -1;
}

Domain Repository::getElement(int position) {
    return this->repo.getElem(position);
}

int Repository::Remove(std::string name) {
    int aux = Find(name);
    if(aux != -1) {
        this->repo.remove(aux);
        return 1;
    }
    return -1;
}

int Repository::getLen() {
    return this->repo.getLength();
}
