
#ifndef SHOPPING_SERVICE_H
#define SHOPPING_SERVICE_H


#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service();
    Service(Repository& repo);
    Repository& getList();
    void addProduct(Product p);

    std::vector <Product> sort_by_category_name();
    std::vector <Product> filter_category(std::string category);
    std::vector <Product> filter_by_name(std::string s);
};


#endif //SHOPPING_SERVICE_H
