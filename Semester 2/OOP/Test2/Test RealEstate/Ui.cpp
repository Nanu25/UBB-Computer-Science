#include <iostream>
#include "Ui.h"
#include "Person.h"
#include "Company.h"

using namespace std;

Ui::Ui(RealEstateAgency agency_list) {
    this->agency_list = agency_list;
}

void print_menu() {
    cout << "1 for remove a client\n";
    cout << "2 for show all clients and all Dwellings\n";
    cout << "3 for add a new Dwelling\n";
    cout << "4 for write the data to the file\n";
    cout << "0 for exit\n";
}

void Ui::Start() {
    auto p1 = new Person("Alex", 10);
    auto p2 = new Person("Alexandra", 1000);
    auto c1 = new Company("NN", 50, 100);
    auto c2 = new Company("ING", 10, 20);

    this->agency_list.addDwelling(100, 1);
    this->agency_list.addClient(c1);
    this->agency_list.addClient(c2);
    this->agency_list.addClient(p1);
    this->agency_list.addClient(p2);

    int ok = 1;
    while(ok) {
        print_menu();
        int option;
        cin >> option;

        if(option == 1) {
            string name;
            cout << "Tell the client name";
            cin >> name;

            this->agency_list.removeClient(name);
        }else if(option == 2) {
            cout << "Clients\n";
            for(auto e : this->agency_list.getClients())
                cout << e->toString() << '\n';

            cout << "Dwellings\n";
            for(auto e : this->agency_list.getDwellings())
                cout << "Price: " << e->getPrice() << " Is profitable " << e->getProfitable() << '\n';


        }else if(option == 3) {
            int price;
            cout << "Tell the Dwelling price";
            cin >> price;

            bool inter;
            cout << "Is profitable?\n1 for yes\n0 for no";
            cin >> inter;

            this->agency_list.addDwelling(price, inter);

            Dwelling x(price, inter);
            vector <Client*> aux = this->agency_list.getInterestedClients(x);
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 4) {
            cout << "Tell the filename";
            string s;
            cin >> s;

            this->agency_list.writeToFile(s);
        }else break;

    }
}

