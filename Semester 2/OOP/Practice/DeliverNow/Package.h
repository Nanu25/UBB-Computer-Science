
#ifndef DELIVERNOW_PACKAGE_H
#define DELIVERNOW_PACKAGE_H


#include <string>

class Package {
private:
    std::string recipient, street;
    int locX, locY;
    bool delivered;
public:
    Package(std::string recipient, std::string street, int locX, int locY, bool delivered);
    std::string getRecipient();
    std::string getStreet();
    int getLocX();
    int getLocY();
    bool getDelivery();
    void setDelivery();
};


#endif //DELIVERNOW_PACKAGE_H
