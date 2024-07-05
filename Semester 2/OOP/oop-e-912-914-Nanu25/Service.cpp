//
// Created by alex_ on 6/27/2024.
//

#include <algorithm>
#include "Service.h"

Service::Service(Repository &repo) : serv_ideea(repo){

}

Repository &Service::getServIdeea() {
    return this->serv_ideea;
}

void Service::AddIdeeaServ(Ideea i) {
    this->serv_ideea.addIdeea(i);
}

bool cmp(Ideea i1, Ideea i2) {
    return i1.getYear() < i2.getYear();
}

void Service::sortDuration() {
    std::sort(this->serv_ideea.getIdeeaRepo().begin(), this->serv_ideea.getIdeeaRepo().end(), cmp);

}

std::vector<Ideea> Service::getAcceptedIdeeas(std::string name) {
    std::vector <Ideea> aux;
    for(auto e : this->serv_ideea.getIdeeaRepo()) {
        if(e.getStatus() == "accepted" && e.getCreator() == name)
            aux.push_back(e);
    }
    return aux;
}

void Service::ChangeDescription(std::string title, std::string creator, std::string newdesc) {
    for(int i = 0; i < this->serv_ideea.getIdeeaRepo().size(); i++)
        if(this->serv_ideea.getIdeeaRepo()[i].getCreator() == creator && this->serv_ideea.getIdeeaRepo()[i].getTitle() == title)
            this->serv_ideea.getIdeeaRepo()[i].setDescription(newdesc);
}
