
#ifndef EVENTPLANNER_REPOSITORY_H
#define EVENTPLANNER_REPOSITORY_H


#include <vector>
#include "Event.h"
#include "Person.h"

class Repository {
private:
    std::vector <Event> event_repo;
    std::vector <Person> person_repo;
public:

    std::vector <Event>& getEventRepo();
    std::vector <Person>& getPersonRepo();

    void addEvent(Event e);
    void readFile();

};


#endif //EVENTPLANNER_REPOSITORY_H
