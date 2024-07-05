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

    std::vector <Gui*> guis;
    for(auto e : repo.getCourrierRepo()) {
        Gui* curr = new Gui{serv, e.getName(), e.getX(), e.getY(), e.getR(), e.getStreets()};
        guis.push_back(curr);
        curr->show();
        curr->setTitle();
        serv.addObserver(curr);
    }
    std::vector<std::string > s;
    Gui* curr = new Gui{serv, "company", 0, 0, 0,  s};
    curr->show();
    serv.addObserver(curr);

    return a.exec();
}
