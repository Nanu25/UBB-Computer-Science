
#ifndef SHOPPING_REPOSITORY_H
#define SHOPPING_REPOSITORY_H


#include <vector>
#include "../Domain/Product.h"

class Repository {
private:
    std::vector <Product> repo;
public:
    Repository();
    std::vector <Product> getRepo();
    void add(Product p);
    void load_file(std::string filename);
};


#endif //SHOPPING_REPOSITORY_H
