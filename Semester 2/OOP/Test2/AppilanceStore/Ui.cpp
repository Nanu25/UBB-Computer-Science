#include <iostream>
#include "Ui.h"
#include "Refrigerator.h"
#include "DishWasher.h"

using namespace std;

Ui::Ui(Service serv) {
    this->serv_list = serv;
}

void print_menu() {
    cout << "1 for add a new appliance\n";
    cout << "2 for show all appliances\n";
    cout << "3 for show all efficient appliances\n";
    cout << "4 to save all appliances that have consumed energy more than a given value\n";
    cout << "0 for exit\n";
}

void Ui::Start() {
    auto a1 = new Refrigerator("2", 10, "A+", 1);
    auto a2 = new DishWasher("1", 25, 20, 10);
    auto a3 = new Refrigerator("5", 100, "A++", 0);

    this->serv_list.addAppliance(a1);
    this->serv_list.addAppliance(a2);
    this->serv_list.addAppliance(a3);

    while(1) {
        print_menu();

        int option;
        cin >> option;

        if(option == 1){
            cout << "1 for add a Refrigerator\n";
            cout << "2 for add a DishWasher\n";
            int opt;
            cin >> opt;

            string id;
            cout << "Tell id\n";
            cin >> id;

            cout << "Tell the weight\n";
            double weight;
            cin >> weight;

            if(opt == 1) {
                cout << "Tell the electricity class\n";
                string clasa;
                cin >> clasa;

                cout << "It has a refrigerator?(0/1)\n";
                bool ok;
                cin >> ok;

                auto a = new Refrigerator(id, weight, clasa, ok);
                this->serv_list.addAppliance(a);
            }else {
                cout << "Tell the washing cycle lenght\n";
                int len;
                cin >> len;

                cout << "Tell the consumed energy per hour\n";
                int hour;
                cin >> hour;

                auto a = new DishWasher(id, weight, len, hour);
                this->serv_list.addAppliance(a);

            }

        }else if(option == 2) {
            vector<Appliance*> aux = this->serv_list.getAllAppliances();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 3) {
            cout << "Tell the amouth of energy\n";
            double energy;
            cin >> energy;
            vector<Appliance*> aux = this->serv_list.getAllWithConsumedElectricityLessThan(energy);
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 4) {
            cout << "Tell the amouth of energy\n";
            double energy;
            cin >> energy;

            cout << "Tell the filename\n";
            string filename;
            cin >> filename;

            this->serv_list.writeToFile(filename, energy);

        }else break;
    }
}
