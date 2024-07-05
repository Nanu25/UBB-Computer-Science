
#ifndef SEARCHENGINE_SERVICE_H
#define SEARCHENGINE_SERVICE_H


#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service(Repository& repo);
    Repository& getList();

    std::vector<Document> sortName();
    std::vector<Document> getFiltered(std::string s);
    std::string getBestMatching(std::string s);

};


#endif //SEARCHENGINE_SERVICE_H
