#include <QtWidgets/QApplication>
#include <iostream>
#include "Domain/Task.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "GUI/Gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Task t{"asadsad", 123, 2};
    Repository repo;
    repo.load_file("../input.txt");
    repo.add(t);
    Service serv{repo};
    serv.addTask(Task{"sadasd", 123, 1});
    Gui gui{serv};
    gui.show();

    return a.exec();
}
