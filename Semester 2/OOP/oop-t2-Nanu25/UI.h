#pragma once

#include "Service.h"

class UI {
private:
    Service serv_list;
public:
    UI(Service serv);
    void Start();
};


