#include "Domain/Movie.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "UI/Ui.h"
#include "Tests/tests.h"
#include "FileRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"

using namespace std;



int main() {
    tests T;
    T.testAll();
    //Repository repo_list;
    //Repository movie_list;

    int option;
    cout << "Choose the file type\n";
    cout << "1 for CSV\n";
    cout << "2 for HTML\n";
    cin >> option;
    if(option == 1) {
        CSVRepository repo_list("../repo.csv");
        CSVRepository movie_list("../userWatchlist.csv");

        Service serv_list{repo_list};
        Service user_list{movie_list};

        serv_list.load_repo_file("../repo_data");
        user_list.load_repo_file("../watchlist_data");

        Ui UI{serv_list, user_list};
        UI.start();
    }else {
        HTMLRepository repo_list{"repo.html"};
        HTMLRepository movie_list{"../watchList.html"};

        Service serv_list{repo_list};
        Service user_list{movie_list};

        serv_list.load_repo_file("../repo_data");
        user_list.load_repo_file("../watchlist_data");

        Ui UI{serv_list, user_list};
        UI.start();
    }

    return 0;
}