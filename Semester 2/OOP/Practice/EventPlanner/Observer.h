#ifndef EVENTPLANNER_OBSERVER_H
#define EVENTPLANNER_OBSERVER_H


#include <vector>

class Observer {
public:
    virtual void update() = 0;
    ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> obs;
public:
    void addObserver(Observer *o);
    void notify();

public:

};


#endif //EVENTPLANNER_OBSERVER_H
