#include <QApplication>
#include <iostream>
#include "Repository.h"
#include "gui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo{};
    repo.readFile();
    Service serv{repo};
    serv.sortDuration();

//    for(auto e : repo.getResRepo()) {
//        std::cout << e.getPosition() << " ";
//    }

    std::vector<Gui*> guis;
    for(auto e : repo.getResRepo()) {
        Gui* g = new Gui{serv, e.getName(), e.getPosition()};
        g->show();
        g->setTitle();
        guis.push_back(g);
        serv.addObserver(g);
    }

    return a.exec();
}
