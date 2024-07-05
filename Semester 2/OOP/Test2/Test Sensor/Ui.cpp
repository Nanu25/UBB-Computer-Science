#include <iostream>
#include "Ui.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "SmokeSensor.h"

using namespace std;

Ui::Ui(Device serv){
    this->serv_list = serv;
}

void print_menu() {
    cout << "1 for add a new sensor\n";
    cout << "2 for display all the sensors\n";
    cout << "3 Show the sensors that emit alerts\n";
    cout << "4 to save all the sensors that have the prices lower than a value to a file\n";
}

void Ui::Start() {
    auto s1 = new TemperatureSensor("Samsung", {10, 15, 20}, 20, 30);
    auto s2 = new HumiditySensor("Apple", {35, 40});
    auto s3 = new SmokeSensor("Xiaomi", {1500, 1700});
    this->serv_list.addSensor(s1);
    this->serv_list.addSensor(s2);
    this->serv_list.addSensor(s3);

    while(true)  {
        print_menu();

        int option;
        cin >> option;

        if(option == 1) {
            int opt;
            cout << "1 for Temperature sensor\n";
            cout << "2 for Humidity sensor\n";
            cout << "3 for Smoke sensor\n";
            cin >> opt;

            cout << "Producer\n";
            std::string  producer;
            cin >> producer;

            int n;
            vector <double> reco;
            cout << "Number of recordings and the recordings\n";
            cin >> n;
            for(int i = 1; i <= n; i++) {
                double x;
                cin >> x;
                reco.push_back(x);
            }

            if(opt == 1) {
                cout << "Diametre\n";
                double dia;
                cin >> dia;

                cout << "Length\n";
                double len;
                cin >> len;

                auto s = new TemperatureSensor(producer, reco, dia, len);
                this->serv_list.addSensor(s);
            }else if(option == 2) {
                auto s = new HumiditySensor(producer, reco);
                this->serv_list.addSensor(s);
            }else {
                auto s = new SmokeSensor(producer, reco);
                this->serv_list.addSensor(s);
            }
        }else if(option == 2) {
            vector <Sensor*> aux = this->serv_list.getAllSensors();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 3) {
            vector <Sensor*> aux = this->serv_list.getAlertingSensors();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 4) {
            double price;
            cout << "Tell the price\n";
            cin >> price;

            string filename;
            cout << "Tell the filename\n";
            cin >> filename;


            this->serv_list.writeToFile(filename, price);
        }else break;
    }
}
