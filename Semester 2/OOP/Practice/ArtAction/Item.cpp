
#include "Item.h"

Item::Item(std::string name, std::string category, int price) {
    this->name = name;
    this->category = category;
    this->price = price;
}

int Item::getPrice() {
    return this->price;
}

std::string Item::getName() {
    return this->name;
}

std::string Item::toString() {
    return this->name + " " + this->category + " " + std::to_string(this->price);
}

void Item::addOffert(std::tuple<int, std::string, int> elem) {
    this->offerts.push_back(elem);
}

std::string Item::getCategory() {
    return this->category;
}

std::vector<std::tuple<int, std::string, int>> Item::getOfferts() {
    return this->offerts;
}

void Item::setPrice(int price) {
    this->price = price;
}
