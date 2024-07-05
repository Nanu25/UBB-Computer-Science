
#ifndef SHOPPING_PRODUCT_H
#define SHOPPING_PRODUCT_H


#include <string>

class Product {
private:
    std::string category, name;
    int quantity;
public:
    Product();
    Product(std::string category, std::string name, int quantity);
    std::string getCategory();
    std::string getName();
    std::string toStr();
    int getQuantity();
};


#endif //SHOPPING_PRODUCT_H
