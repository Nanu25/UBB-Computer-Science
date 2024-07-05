
#ifndef ARTACTION_REPOSITORY_H
#define ARTACTION_REPOSITORY_H


#include <vector>
#include "User.h"
#include "Item.h"

class Repository {
private:
    std::vector <User> user_repo;
    std::vector <Item> item_repo;
public:
    void addUser(User u);
    void addItem(Item i);

    std::vector<Item>& getItemRepo();
    std::vector<User>& getUserRepo();

    void readFile();
    void writeFile();
};


#endif //ARTACTION_REPOSITORY_H
