
#ifndef BILLS_SERVICE_H
#define BILLS_SERVICE_H


#include "../Repository/Repository.h"

class Service {
private:
    Repository& serv_list;
public:
    Service(Repository& serv_list);
    Repository& getList();
    std::vector<Bills> sort_by_company();
    std::vector <Bills> filter_paid_unpaid(std::string s);
    std::vector <Bills> filter_company_name(std::string s);

};


#endif //BILLS_SERVICE_H
