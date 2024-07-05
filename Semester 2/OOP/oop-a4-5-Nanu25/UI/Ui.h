#pragma once
#include "../Service/Service.h"

class Ui {
    Service service_list;
public:
    Ui(Service serv_list);
    void start(Service user_list);

};


