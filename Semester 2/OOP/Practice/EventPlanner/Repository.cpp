
#include <fstream>
#include "Repository.h"

std::vector<Event> &Repository::getEventRepo() {
    return this->event_repo;
}

std::vector<Person> &Repository::getPersonRepo() {
    return this->person_repo;
}

void Repository::addEvent(Event e) {
    for(auto it : this->event_repo)
        if(it.getEventName() == e.getEventName() && e.getEventLocation() == it.getEventLocation())
                throw std::runtime_error("Already exists");
    this->event_repo.push_back(e);
}

void Repository::readFile() {
    std::ifstream fin("../person.txt");
    std::string line;
    while(std::getline(fin, line)) {
        std::string name = "";
        int index = 0;
        while(line[index] != ',')
            name += line[index++];
        index++;

        std::string xloc = "";
        while(line[index] != ',')
            xloc += line[index++];
        index++;

        std::string yloc = "";
        while(line[index] != ',')
            yloc += line[index++];
        index++;

        bool del = line[index] - '0';
        this->person_repo.push_back(Person{name, xloc + " " + yloc, del});
    }

    fin.close();

    std::ifstream f("../event.txt");
    while(std::getline(f, line)) {
        int index = 0;
        std::string org = "";
        while(line[index] != ',')
            org += line[index++];
        index++;

        std::string name = "";
        while(line[index] != ',')
            name += line[index++];
        index++;

        std::string desc = "";
        while(line[index] != ',')
            desc += line[index++];
        index++;

        std::string xloc = "";
        while(line[index] != ',')
            xloc += line[index++];
        index++;

        std::string yloc = "";
        while(line[index] != ',')
            yloc += line[index++];
        index++;

        std::string date = "";
        while(index < line.size())
            date += line[index++];

        this->event_repo.push_back(Event{org, name, desc, xloc + " " + yloc, date});
    }

    f.close();
}
