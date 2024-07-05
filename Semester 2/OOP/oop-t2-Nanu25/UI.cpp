
#include <iostream>
#include "UI.h"
#include "Block.h"
#include "House.h"

using namespace std;

UI::UI(Service serv) {
    this->serv_list = serv;
}

void print_menu() {
    cout << "1 for add a new building\n";
    cout << "2 for show all the buildings\n";
    cout << "3 for show all the buildings that must be restored in a given year\n";
    cout << "4 to save all the buildings that must be restored and that must be demolished to different files\n";
    cout << "0 for exit\n";
}

void UI::Start() {
    auto b1 = new Block(1900, 100, 50);
    auto b2 = new Block(2000, 100, 90);
    auto b3 = new Block(1960, 100, 85);
    auto b4 = new Block(1960, 100, 3);
    auto h1 = new House(1910, 1);
    auto h2 = new House(1910, 0);
    auto h3 = new House(2000, 0);

    this->serv_list.addBuilding(b1);
    this->serv_list.addBuilding(b2);
    this->serv_list.addBuilding(b3);
    this->serv_list.addBuilding(b4);

    this->serv_list.addBuilding(h1);
    this->serv_list.addBuilding(h2);
    this->serv_list.addBuilding(h3);

    while(1) {
        print_menu();

        int option;
        cin >> option;
        if(option == 1) {
            cout << "1 for add a block\n";
            cout << "2 for add a house\n";

            int opt;
            cin >> opt;

            cout << "Construction year\n";
            int year;
            cin >> year;

            if(opt == 1) {
                cout << "Number of appartaments\n";
                int nra;
                cin >> nra;

                cout << "Number of occupied appartaments\n";
                int nroc;
                cin >> nroc;

                auto b = new Block(year, nra, nroc);
                this->serv_list.addBuilding(b);
            }else {
                cout << "Is this house historycal?(0/1)\n";

                bool ok;
                cin >> ok;

                auto h = new House(year, ok);
                this->serv_list.addBuilding(h);
            }
        }else if(option == 2) {
            vector<Building*> aux = this->serv_list.getAllBuildings();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 3) {
            vector<Building*> aux = this->serv_list.getAllToBeRestored();

            cout << "Tell the year of construction\n";
            int year;
            cin >> year;

            aux = this->serv_list.getAllToBeRestoredGivenYear(aux, year);
            for(auto e : aux)
                cout << e->toString() << '\n';

        }else if(option == 4) {
            cout << "Tell the file name for restored buildings\n";
            string name1;
            cin >> name1;

            cout << "Tell the filename for the demolished buildings\n";
            string name2;
            cin >> name2;

            vector<Building*> aux1 = this->serv_list.getAllToBeRestored();
            vector<Building*> aux2 = this->serv_list.getAllToBeDemolished();

            this->serv_list.writeToFile(name1, aux1);
            this->serv_list.writeToFile(name2, aux2);

        }else break;
    }
}
