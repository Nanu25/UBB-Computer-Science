//
// Created by alex_ on 6/27/2024.
//

#include "Ideea.h"



Ideea::Ideea(std::string title, std::string description, std::string status, std::string creator, int year) {
    this->title = title;
    this->description = description;
    this->status = status;
    this->creator = creator;
    this->year = year;
}

std::string Ideea::getTitle() {
    return this->title;
}

std::string Ideea::getDescription() {
    return this->description;
}

std::string Ideea::getStatus() {
    return this->status;
}

std::string Ideea::getCreator() {
    return this->creator;
}

int Ideea::getYear() {
    return this->year;
}

void Ideea::setStatus(std::string st) {
    this->status = st;
}

void Ideea::setDescription(std::string desc) {
    this->description = desc;
}
