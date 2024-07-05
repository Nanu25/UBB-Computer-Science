
#ifndef OOP_E_912_914_NANU25_SERVICE_H
#define OOP_E_912_914_NANU25_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service : public Subject{
private:
    Repository& serv_ideea;
public:
    Service(Repository& repo);

    Repository& getServIdeea();
    void AddIdeeaServ(Ideea i);
    void sortDuration();
    std::vector <Ideea> getAcceptedIdeeas(std::string  name);

    void ChangeDescription(std::string title, std::string creator, std::string newdesc);
};

#endif //OOP_E_912_914_NANU25_SERVICE_H
