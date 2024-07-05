
#include "Product.h"

Product::Product(std::string category, std::string name, int quantity) {
    this->category = category;
    this->name = name;
    this->quantity = quantity;
}

std::string Product::getCategory() {
    return this->category;
}

std::string Product::getName() {
    return this->name;
}

std::string Product::toStr() {
    return this->category + " " + this->name + " " + std::to_string(this->quantity);
}

int Product::getQuantity() {
    return this->quantity;
}
