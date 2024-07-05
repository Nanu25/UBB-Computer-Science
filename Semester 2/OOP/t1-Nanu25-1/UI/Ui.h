#pragma once

#include "../Service/Service.h"

class Ui {
private:
    Service serv_list;

public:
    Ui(Service serv);
    void Start();
};


