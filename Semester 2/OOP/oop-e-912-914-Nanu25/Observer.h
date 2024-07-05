
#ifndef OOP_E_912_914_NANU25_OBSERVER_H
#define OOP_E_912_914_NANU25_OBSERVER_H


#include <vector>

class Observer {
public:
    virtual void update() = 0;
    ~Observer() = default;
};

class Subject {
private:
    std::vector <Observer*> obs;
public:
    void addObserver(Observer* o);
    void notify();

};



#endif //OOP_E_912_914_NANU25_OBSERVER_H
