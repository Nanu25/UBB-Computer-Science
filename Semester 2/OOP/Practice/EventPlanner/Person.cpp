
#include "Person.h"

Person::Person(std::string name, std::string location, bool organiser) : name{name}, location{location}, organiser{organiser}{

}

std::string Person::getName() {
    return this->name;
}

std::string Person::getLocation() {
    return this->location;
}

bool Person::getOrganiser() {
    return this->organiser;
}
