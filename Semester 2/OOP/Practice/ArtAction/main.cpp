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
    serv.sortByPrice();

    std::vector <GUI*> guis;
    for(auto e : repo.getUserRepo()) {
        GUI* usergui = new GUI{serv, e.getName(), e.getType(), e.getId()};
        serv.addObserver(usergui);
        usergui->setTitle();
        usergui->show();
        guis.push_back(usergui);
    }

    return a.exec();
}
