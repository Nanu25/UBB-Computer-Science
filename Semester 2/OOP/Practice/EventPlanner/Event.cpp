
#include "Event.h"

Event::Event(std::string org, std::string name, std::string desc, std::string loc, std::string date) : organiser(org), name{name}, description(desc), location(loc), date{date}{

}

std::string Event::getOrganiser() {
    return this->organiser;
}

std::string Event::getEventName() {
    return this->name;
}

std::string Event::getDescription() {
    return this->description;
}

std::string Event::getEventLocation() {
    return this->location;
}

std::string Event::getDate() {
    return this->date;
}
