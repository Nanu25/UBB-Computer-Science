
#include "User.h"

User::User(std::string name, int id, std::string type) : name{name}, id{id}, type{type} {

}

std::string User::getName() {
    return this->name;
}

std::string User::getType() {
    return this->type;
}

int User::getId() {
    return this->id;
}
