//
// Created by alex_ on 5/23/2024.
//

#include "Task.h"

Task::Task(std::string name, int duration, int priority) {
    this->name = name;
    this->duration = duration;
    this->priority = priority;
}

int Task::getDuration() {
    return this->duration;
}

int Task::getPriority() {
    return this->priority;
}

std::string Task::toStr() {
    return this->name + " " + std::to_string(this->duration) + " " + std::to_string(this->priority);
}
