
#ifndef ARTACTION_SERVICE_H
#define ARTACTION_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service : public Subject {
private:
    Repository& item_serv;
public:
    Service(Repository& repo);
    void addItem(Item i);
    void sortByPrice();
    Repository& getServiceItem();
    void saveFileRepo();
    std::vector <std::string> getAllCategories();
};


#endif //ARTACTION_SERVICE_H
