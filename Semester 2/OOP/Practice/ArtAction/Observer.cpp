#include "Observer.h"

void Subject::addObserver(Observer *obs) {
    this->observers.push_back(obs);
}

void Subject::notify() {
    for(auto e : this->observers)
        e->update();
}
