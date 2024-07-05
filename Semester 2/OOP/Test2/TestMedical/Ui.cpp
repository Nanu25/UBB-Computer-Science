#include <iostream>
#include "Ui.h"
#include "BP.h"
#include "BMI.h"

using namespace std;

//Ui::Ui() {
//
//}

Ui::Ui(Person serv) {
    this->serv_list = serv;
}

void print_menu() {
    cout << "1 for add a new analysis\n";
    cout << "2 for show all the analysis\n";
    cout << "3 for show if a person is ill\n";
    cout << "4 for save the analysis between 2 dates to a given file\n";
}

void Ui::Start() {
    auto a1 = new BP("2024.02.25", 95, 65);
    auto a2 = new BMI("2024.02.22", 15);
    auto a3 = new BMI("2023.04.20", 20);
    this->serv_list.addAnalysis(a1);
    this->serv_list.addAnalysis(a2);
    this->serv_list.addAnalysis(a3);

    while(1) {
        print_menu();
        int option;

        cin >> option;

        if(option == 1) {
            cout << "1 for add BMI analysis\n";
            cout << "2 for BP analysis\n";

            int opt;
            cin >> opt;

            cout << "Date: \n";
            string date;
            cin >> date;

            if(opt == 1) {
                cout << "Tell the value\n";

                double value;
                cin >> value;

                auto a = new BMI(date, value);
                this->serv_list.addAnalysis(a);
            }else {
                cout << "Tell the systolic value\n";
                int sys;
                cin >> sys;

                int dia;
                cout << "Tell the dialostic value\n";
                cin >> dia;

                auto a = new BP(date, sys, dia);
                this->serv_list.addAnalysis(a);
            }
        }else if(option == 2) {
            vector<MedicalAnalysis*> aux = this->serv_list.getAllAnalysis();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 3) {
            cout << "Tell the number of month\n";
            int month;
            cin >> month;

            bool ok = this->serv_list.isIll(month);
            if(ok == 1)
                cout << "The person is not ill\n";
            else
                cout << "The person is ill\n";

        }else if(option == 4) {
            string filename;
            cout << "Tell the filename\n";
            cin >> filename;

            string d1;
            cout << "Tell the first date\n";
            cin >> d1;

            string d2;
            cout << "Tell the second date\n";
            cin >> d2;

            this->serv_list.writeToFile(filename, d1, d2);
        }else break;
    }

}
