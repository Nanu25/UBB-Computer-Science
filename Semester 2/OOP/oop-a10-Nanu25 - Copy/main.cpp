#include <QtWidgets/QApplication>
#include "Domain/Movie.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "UI/Ui.h"
#include "Tests/tests.h"
#include "Repository/FileRepository.h"
#include "Repository/CSVRepository.h"
#include "Repository/HTMLRepository.h"
#include "UI/GUI.h"
#include "UI/GUIWithDesigner.h"
#include "UI/gui_user.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CSVRepository repo{ "../repo.csv" };
    CSVRepository user_repo{"../userWatchlist.csv"};
    Service serv{ repo };
    Service user_list{user_repo};
    serv.load_repo_file("../repo.csv");
    user_list.load_repo_file("../userWatchlist.csv");
    GUIWithDesigner gui{ serv , user_list};
    GUI_USER gui_user{serv, user_list};
    serv.addObserver(&gui);
    serv.addObserver(&gui_user);
    gui.setTitle();
    gui_user.setTitle();
    gui.show();
    gui_user.show();


    return a.exec();
}
