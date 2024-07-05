
#include <algorithm>
#include "Service.h"

Service::Service(Repository &repo) : serv_list{repo}{

}

Repository &Service::getList() {
    return this->serv_list;
}

bool cmp(Document d1, Document d2) {
    return d1.getName() < d2.getName();
}

std::vector<Document> Service::sortName() {
    std::vector<Document> aux = this->serv_list.getRepo();
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

std::vector<Document> Service::getFiltered(std::string s) {
    std::vector <Document> aux;
    for(auto e : this->serv_list.getRepo()) {
        if(e.getName().find(s) != std::string::npos || e.getKeyword().find(s) != std::string::npos)
            aux.push_back(e);
    }
    return aux;
}

std::string Service::getBestMatching(std::string s) {
    std::string result;
    double max1 = 0.0;
    for(auto e : this->serv_list.getRepo()) {
        if(e.getName().find(s) != std::string::npos) {
            double x = (double)s.size() / e.getName().size();
            if(x > max1) {
                max1 = x;
                result = e.getName();
            }
        }
    }

    return result;
}
