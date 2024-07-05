
#ifndef SEARCHENGINE_REPOSITORY_H
#define SEARCHENGINE_REPOSITORY_H


#include <vector>
#include "../Domain/Document.h"

class Repository {
private:
    std::vector <Document> repo;
public:
    std::vector <Document> getRepo();
    void load_file(std::string filename);
};


#endif //SEARCHENGINE_REPOSITORY_H
