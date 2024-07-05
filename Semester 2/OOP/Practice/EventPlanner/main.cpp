#include <QApplication>
#include <iostream>
#include "Repository.h"
#include "Service.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo{};
    repo.readFile();
    Service serv{repo};
    serv.sortDate();

    std::vector<Gui*> guis;
    for(auto e : repo.getPersonRepo()) {
        Gui* g = new Gui{serv, e.getName(), e.getLocation(), e.getOrganiser()};
        g->setTitle();
        g->show();
        guis.push_back(g);
        serv.addObserver(g);
    }



    return a.exec();
}
