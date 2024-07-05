
#include <algorithm>
#include <unordered_map>
#include "Service.h"

Service::Service(Repository &repo) : item_serv{repo} {

}

bool cmp(Item i1, Item i2) {
    return i1.getPrice() < i2.getPrice();
}

void Service::sortByPrice() {
    std::sort(this->item_serv.getItemRepo().begin(), this->item_serv.getItemRepo().end(), cmp);
}

Repository &Service::getServiceItem() {
    return this->item_serv;
}

std::vector<std::string> Service::getAllCategories() {
    std::unordered_map <std::string, int> M;
    std::vector <std::string> aux;
    for(auto e : this->item_serv.getItemRepo())
        if(M[e.getCategory()] == 0) {
            aux.push_back(e.getCategory());
            M[e.getCategory()] = 1;
        }
    return aux;
}

void Service::addItem(Item i) {
    this->item_serv.addItem(i);
    this->notify();
}

void Service::saveFileRepo() {
    this->item_serv.writeFile();
}
