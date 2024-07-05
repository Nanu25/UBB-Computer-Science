
#ifndef ARTACTION_USER_H
#define ARTACTION_USER_H


#include <string>

class User {
private:
    std::string name, type;
    int id;
public:
    User(std::string name, int id, std::string type);
    std::string getName();
    std::string getType();
    int getId();
};


#endif //ARTACTION_USER_H
