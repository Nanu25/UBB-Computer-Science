//
// Created by alex_ on 6/27/2024.
//

#include "Researcher.h"

Researcher::Researcher(std::string name, std::string position) : name{name}, position{position}{

}

std::string Researcher::getName() {
    return this->name;
}

std::string Researcher::getPosition() {
    return this->position;
}
