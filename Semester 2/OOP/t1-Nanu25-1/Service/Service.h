#pragma once
#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service(Repository &serv);

    int AddPlayer(TElement x);
    int RemovePlayer(std::string name);
    DynamicArray get_player_given_nato(std::string nato);
    Repository& getrepo();
};


