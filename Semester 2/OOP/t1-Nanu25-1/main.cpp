#include <iostream>
#include "Domain/Domain.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "UI/Ui.h"
#include "Tests/Test.h"

int main() {
    Test t;
    t.test();
   // Domain a{"Cristina", "ROU", "CSM", 100};
    Repository repo;
    Service serv{repo};
    //serv.AddPlayer(a);
    Ui ui{serv};
    ui.Start();

    return 0;
}
