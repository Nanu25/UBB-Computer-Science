#pragma once

#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service();
    Service(Repository &repo);
    void addTask(Task t);
    Repository& getList();
    std::vector <Task> sort_by_pd();
    std::vector <Task> filter_priority(int p);
};


