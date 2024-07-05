//
// Created by alex_ on 6/27/2024.
//

#ifndef OOP_E_912_914_NANU25_IDEEA_H
#define OOP_E_912_914_NANU25_IDEEA_H


#include <string>

class Ideea {
private:
    std::string title, description, status, creator;
    int year;
public:
    Ideea(std::string title, std::string description, std::string status, std::string creator, int year);
    std::string getTitle();
    std::string getDescription();
    std::string getStatus();
    std::string getCreator();
    int getYear();
    void setStatus(std::string st);
    void setDescription(std::string desc);
};


#endif //OOP_E_912_914_NANU25_IDEEA_H
