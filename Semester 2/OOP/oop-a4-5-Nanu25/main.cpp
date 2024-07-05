#include "Domain/Movie.h"
#include "DynamicArray/DynamicArray.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "UI/Ui.h"
#include "Tests/tests.h"

using namespace std;
int main() {
    tests T;
    T.testAll();

    Repository repo_list;
    Repository movie_list;

    Service serv_list{movie_list};
    Service user_list{repo_list};
    Ui UI{serv_list};
    UI.start(user_list);

    return 0;
}