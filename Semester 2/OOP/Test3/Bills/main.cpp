#include <QtWidgets/QApplication>
#include "Gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    repo.load_file("../input.txt");
    Service serv{repo};
    Gui gui{serv};
    gui.show();

    return a.exec();
}
