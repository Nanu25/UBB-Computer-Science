#include <iostream>
#include "Ui.h"
#include "NeonataUnit.h"
#include "Surgery.h"

using namespace std;

Ui::Ui(Service serv) {
    this->serv_list = serv;
}

void print_menu() {
    cout << "1 for add a new department\n";
    cout << "2 for show all departments\n";
    cout << "3 for show all efficient department\n";
    cout << "4 to save all the departments in a given file\n";
    cout << "0 for exit\n";
}

void Ui::Start() {
    auto d1 = new NeonatalUnit("Transilvania", 10, 20, 30, 9.5);
    auto d2 = new Surgery("ClujHospital", 20, 40);
    auto d3 = new NeonatalUnit("ATI", 50, 30, 60, 4.5);

    this->serv_list.addDepartment(d1);
    this->serv_list.addDepartment(d2);
    this->serv_list.addDepartment(d3);

    while(1) {
        print_menu();

        int option;
        cin >> option;

        if(option == 1) {
            cout << "1 for Surgery department\n";
            cout << "2 for neonatal department\n";
            int opt;
            cin >> opt;

            cout << "Hospital name\n";
            string name;
            cin >> name;

            cout << "Number of doctors\n";
            int nrd;
            cin >> nrd;

            if(opt == 1) {
                cout << "Number of patients\n";
                int nrp;
                cin >> nrp;

                auto d = new Surgery(name, nrd, nrp);
                this->serv_list.addDepartment(d);
            }else {
                cout << "Number of mothers\n";
                int nrm;
                cin >> nrm;

                cout << "Number of babies\n";
                int nrb;
                cin >> nrb;

                cout << "Avrage grade\n";
                double avg;
                cin >> avg;

                auto d = new NeonatalUnit(name, nrd, nrm, nrb, avg);
                this->serv_list.addDepartment(d);
            }

        }else if(option == 2) {
            vector <HospitalDepartment*> aux = this->serv_list.getAllDepartment();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 3) {
            vector <HospitalDepartment*> aux = this->serv_list.getAllEfficientDepartments();
            for(auto e : aux)
                cout << e->toString() << '\n';
        }else if(option == 4) {
            cout << "Tell the filename\n";
            string s;
            cin >> s;
            this->serv_list.writeToFile(s);
        }else break;

    }

}
