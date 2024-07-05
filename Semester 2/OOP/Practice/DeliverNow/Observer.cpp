
#include "Observer.h"

void Subject::addObserver(Observer *o) {
    this->obs.push_back(o);
}

void Subject::notify() {
    for(auto e : this->obs)
        e->update();
}
