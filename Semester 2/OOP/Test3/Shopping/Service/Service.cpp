
#include <algorithm>
#include "Service.h"

Service::Service(Repository &repo) : serv_list{repo} {

}

Repository &Service::getList() {
    return this->serv_list;
}

void Service::addProduct(Product p){
    this->serv_list.add(p);
}

bool cmp(Product p1, Product p2) {
    return p1.getCategory() < p2.getCategory() || (p1.getCategory() == p2.getCategory() && p1.getName() < p2.getName());
}

std::vector<Product> Service::sort_by_category_name() {
    std::vector <Product> aux = this->serv_list.getRepo();
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

bool cmp1(Product p1, Product p2) {
    return p1.getQuantity() < p2.getQuantity();
}

std::vector<Product> Service::filter_category(std::string category) {
    std::vector <Product> aux;
    for(auto e : this->serv_list.getRepo())
        if(e.getCategory() == category)
            aux.push_back(e);

    //sort by category
    std::sort(aux.begin(), aux.end(), cmp1);
    return aux;
}

std::vector<Product> Service::filter_by_name(std::string s) {
    std::vector <Product> aux;
    for(auto e : this->serv_list.getRepo()) {
        if (e.getName().find(s) != std::string::npos)
            aux.push_back(e);
        else if(e.getCategory().find(s) != std::string::npos)
            aux.push_back(e);
    }
    return aux;
}

