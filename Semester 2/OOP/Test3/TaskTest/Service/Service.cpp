
#include <algorithm>
#include "Service.h"

Service::Service(Repository &repo) : serv_list{repo} {

}

void Service::addTask(Task t) {
    this->serv_list.add(t);
}

Repository &Service::getList() {
    return this->serv_list;
}

bool cmp(Task t1, Task t2) {
    return t1.getPriority() < t2.getPriority() || (t1.getPriority() == t2.getPriority() && t1.getDuration() < t2.getDuration());
}

std::vector<Task> Service::sort_by_pd() {
    std::vector <Task> aux = this->serv_list.getRepo();
    std::sort(aux.begin(), aux.end(), cmp);
    return aux;
}

std::vector<Task> Service::filter_priority(int p) {
    std::vector <Task> aux;
    for(auto e : this->serv_list.getRepo())
        if(e.getPriority() == p)
            aux.push_back(e);
    return aux;
}

