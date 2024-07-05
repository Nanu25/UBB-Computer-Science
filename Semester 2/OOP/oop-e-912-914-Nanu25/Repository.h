//
// Created by alex_ on 6/27/2024.
//

#ifndef OOP_E_912_914_NANU25_REPOSITORY_H
#define OOP_E_912_914_NANU25_REPOSITORY_H


#include <vector>
#include "Ideea.h"
#include "Researcher.h"

class Repository {
private:
    std::vector <Ideea> ideea_repo;
    std::vector <Researcher> res_repo;
public:

    std::vector <Researcher>& getResRepo();
    std::vector <Ideea>& getIdeeaRepo();

    void addIdeea(Ideea i1);
    void addResearcher(Researcher r);

    void readFile();
};



#endif //OOP_E_912_914_NANU25_REPOSITORY_H
