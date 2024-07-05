
#include "Development.h"

Development::Development(std::string name, std::string type) {
    this->name = name;
    this->type = type;
}

std::string Development::getName() {
    return this->name;
}

std::string Development::getType() {
    return this->type;
}


