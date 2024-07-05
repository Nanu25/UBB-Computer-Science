
#ifndef EVENTPLANNER_EVENT_H
#define EVENTPLANNER_EVENT_H


#include <string>

class Event {
private:
    std::string organiser, name, description, location, date;
public:
    Event(std::string org, std::string name, std::string desc, std::string loc, std::string date);
    std::string getOrganiser();
    std::string getEventName();
    std::string getDescription();
    std::string getEventLocation();
    std::string getDate();

};


#endif //EVENTPLANNER_EVENT_H
