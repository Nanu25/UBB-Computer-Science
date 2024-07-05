//
// Created by alex_ on 7/1/2024.
//

#include "Observer.h"

void Subject::addObserver(Observer *obs) {
    this->observers.push_back(obs);

}

void Subject::notify() {
    for (auto obs : this->observers) {
        obs->update();
    }
}
