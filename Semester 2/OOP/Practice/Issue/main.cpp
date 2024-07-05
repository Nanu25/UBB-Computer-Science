#include <QApplication>
#include <iostream>
#include <fstream>
#include "gui.h"
#include "Development.h"
#include "Repository.h"
#include "Service.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests t;
    t.testAll();
    Development dev{"sadsa", "programmer"};
    Repository repo{};
    repo.readFile();
    repo.AddDevelopment(dev);
    Service serv{repo};

    std::vector<GUI*> guiWindows;
    for(auto& e : serv.getRepository().getDevoRepo()) {
        GUI* devgui = new GUI{serv, e.getName(), e.getType()};
        serv.addObserver(devgui);
        devgui->setTitle(e.getName() + " " + e.getType());
        devgui->show();
        guiWindows.push_back(devgui);
    }

    std::ofstream fout("../issue.txt");
    for(auto e : serv.getRepository().getIssueRepo()) {
        fout << e.getDescription() << "," << e.getStatus() << "," << e.getReporter() << "," << e.getSolver() << '\n';
    }
    fout.close();

    return a.exec();
}
