
#include <algorithm>
#include "Service.h"

Service::Service(Repository &repo) : serv_list(repo) {

}

Repository &Service::getService() {
    return this->serv_list;
}

void Service::AddEvent(Event e) {
    this->serv_list.addEvent(e);
}

bool cmp(Event a, Event b) {
    return a.getDate() < b.getDate();
}

void Service::sortDate() {
    std::sort(this->serv_list.getEventRepo().begin(), this->serv_list.getEventRepo().end(), cmp);
}
