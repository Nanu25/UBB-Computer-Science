
#include <cassert>
#include "Test.h"
#include "../Repository/Repository.h"
#include "../Service/Service.h"

void Test::test() {
    Repository repo;
    Service serv_list{repo};

    serv_list.AddPlayer(Domain{"Cristina", "ROU", "CSM", 100});
    serv_list.AddPlayer(Domain{"Isa_Gul", "SWE", "BUL", 90});
    serv_list.AddPlayer(Domain{"Donast_Bale", "FRA", "PSG", 150});
    serv_list.AddPlayer(Domain{"Pintea", "ROU", "CSM", 50});
    serv_list.AddPlayer(Domain{"Popescu", "ROU", "CSM", 100});

    serv_list.RemovePlayer("Cristina");
    assert(serv_list.getrepo().getElement(0).getName() == "Isa_Gul");

    serv_list.RemovePlayer("Isa");
    assert(serv_list.getrepo().getElement(0).getName() == "Isa_Gul");

    serv_list.RemovePlayer("Isa_Gul");
    assert(serv_list.getrepo().getElement(0).getName() == "Donast_Bale");


    DynamicArray player = serv_list.get_player_given_nato("ROU");
    assert(player.getElem(0).getGoals() == 50);
    assert(player.getElem(1).getGoals() == 100);
    assert(player.getLength() == 2);

}

