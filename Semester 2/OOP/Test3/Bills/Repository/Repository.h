
#ifndef BILLS_REPOSITORY_H
#define BILLS_REPOSITORY_H


#include <vector>
#include "../Domain/Bills.h"

class Repository {
private:
    std::vector <Bills> repo;
public:
    std::vector <Bills> getRepo();
    void load_file(std::string filename);
};


#endif //BILLS_REPOSITORY_H
