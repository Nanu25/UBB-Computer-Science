
#ifndef EVENTPLANNER_PERSON_H
#define EVENTPLANNER_PERSON_H


#include <string>

class Person {
private:
    std::string name, location;
    bool organiser;
public:
    Person(std::string name, std::string location, bool organiser);
    std::string getName();
    std::string getLocation();
    bool getOrganiser();
};


#endif //EVENTPLANNER_PERSON_H
