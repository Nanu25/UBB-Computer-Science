
#include <algorithm>
#include "Service.h"


Service::Service(Repository &serv_list) : serv_list(serv_list) {

}

Repository &Service::getList() {
    return this->serv_list;
}

bool cmp(Bills b1, Bills b2) {
    return b1.getName() < b2.getName();
}

std::vector<Bills> Service::sort_by_company() {
    std::vector <Bills> aux = this->serv_list.getRepo();
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

std::vector<Bills> Service::filter_paid_unpaid(std::string s) {
    std::vector <Bills> aux;
    for(auto e : this->serv_list.getRepo()) {
        if(e.getPaid().find(s) != std::string::npos)
            aux.push_back(e);
    }
    return aux;
}

std::vector<Bills> Service::filter_company_name(std::string s) {
    std::vector <Bills> aux;
    for(auto e : this->serv_list.getRepo()) {
        if(e.getName() == s && e.getPaid() == "false")
            aux.push_back(e);
    }
    return aux;
}
