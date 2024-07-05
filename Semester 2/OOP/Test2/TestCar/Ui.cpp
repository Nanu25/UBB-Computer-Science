
#include <iostream>
#include "Ui.h"

using namespace std;

void print_menu() {
    cout << "1 for add a new car\n";
    cout << "2 for show all the cars\n";
    cout << "3 for save the data to a file\n";
    cout << "0 for exit\n";
}

void Ui::start() {
    this->serv_list.addCar("Sedan", "electric", "diesel", 700);
    this->serv_list.addCar("Sedan", "turbo", "diesel", 0);
    this->serv_list.addCar("Convertible", "turbo", "gasoline", 0);

    while(1) {
        print_menu();

        int option;
        cin >> option;

        if(option == 1) {
            cout << "Tell the body style(Sedan/Concertible)\n";
            string body;
            cin >> body;

            cout << "Tell the engine type(electric/turbo)\n";
            string engT;
            cin >> engT;

            cout << "Fuel type(diesel/gasoline)\n";
            string fuel;
            cin >> fuel;

            int autonomy = 0;
            if(engT == "electric") {
                cout << "Tell the autonomy\n";
                cin >> autonomy;
            }

            this->serv_list.addCar(body, engT, fuel, autonomy);
            cout << this->serv_list.getCars()[this->serv_list.getCars().size() - 1]->computePrice() << '\n';

        }else if(option == 2) {
            for(auto e : this->serv_list.getCars())
                cout << e->toString() << '\n';
        }else if(option == 3) {
            double maxprice;
            cout << "Tell the maxprice\n";
            cin >> maxprice;

            cout << "Tell the filename\n";
            string fname;
            cin >> fname;

            vector <Car*> aux = this->serv_list.getCarWithMaxPrice(maxprice);
            this->serv_list.writeToFile(fname, aux);
        }else break;
    }

}

Ui::Ui(Service serv) {
    this->serv_list = serv;
}
