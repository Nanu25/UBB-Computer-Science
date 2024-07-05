#include <QtWidgets/QApplication>
#include "Gui/Gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    repo.load_file("../input.txt");
    Service serv{repo};
    Gui g{serv};
    g.show();

    return a.exec();
}
