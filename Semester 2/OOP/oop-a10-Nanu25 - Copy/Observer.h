
#ifndef OOP_A10_NANU25_OBSERVER_H
#define OOP_A10_NANU25_OBSERVER_H


#include <vector>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs);
    void notify();
};


#endif //OOP_A10_NANU25_OBSERVER_H
