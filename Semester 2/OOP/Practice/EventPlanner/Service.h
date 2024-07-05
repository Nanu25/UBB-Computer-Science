
#ifndef EVENTPLANNER_SERVICE_H
#define EVENTPLANNER_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service : public Subject {
private:
    Repository& serv_list;

public:
    Service(Repository &repo);

    Repository& getService();
    void AddEvent(Event e);
    void sortDate();

};


#endif //EVENTPLANNER_SERVICE_H
