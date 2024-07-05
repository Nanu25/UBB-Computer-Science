
#include "Person.h"

bool Person::isInterested(Dwelling x) {
    return (x.getPrice() / 1000 <= this->income);
}

//Person::Person() : {
//}

Person::Person(std::string name, int income): Client(name, income) {
}