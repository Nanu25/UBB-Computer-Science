#pragma once

#include <string>

class Task {
private:
    std::string name;
    int duration, priority;
public:
    Task();
    Task(std::string name, int duration, int priority);
    int getDuration();
    int getPriority();
    std::string toStr();
};


