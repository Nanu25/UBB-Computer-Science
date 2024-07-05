#include <iostream>
#include "Ui.h"

using namespace std;

Ui::Ui(Service serv): serv_list(serv) {

}

void print_menu() {
    cout << "1 for remove a player\n";
    cout << "2 for display all the players\n";
    cout << "3 to show all the players that play for a given nationality\n";
    cout << "0 for exit\n";
}

void print_player(Service player_list) {
    for(int i = 0; i < player_list.getrepo().getLen(); i++) {
        cout << "Player name: " << player_list.getrepo().getElement(i).getName() << '\n';
        cout << "Player nationality: " << player_list.getrepo().getElement(i).getNationality() << '\n';
        cout << "Player team: " << player_list.getrepo().getElement(i).getTeam() << '\n';
        cout << "Number of goals: " << player_list.getrepo().getElement(i).getGoals() << '\n';
        cout << '\n';
    }
}

void Ui::Start() {
    this->serv_list.AddPlayer(Domain{"Cristina", "ROU", "CSM", 100});
    this->serv_list.AddPlayer(Domain{"Isa_Gul", "SWE", "BUL", 90});
    this->serv_list.AddPlayer(Domain{"Donast_Bale", "FRA", "PSG", 150});
    this->serv_list.AddPlayer(Domain{"Pintea", "ROU", "CSM", 50});
    this->serv_list.AddPlayer(Domain{"Messi", "FRA", "CSM", 57});
    this->serv_list.AddPlayer(Domain{"Popescu", "ROU", "CSM", 160});

    while(1) {
        print_menu();
        int option;
        cin >> option;
        if(option == 1) {
            cin.get();
            string input;
            getline(cin, input);

            string name = "";
            int i = 0;
            while(input[i] != '|') {
                if(input[i] == '_' || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
                    name += input[i];
                i++;
            }
            i++;

            string nato = "";
            while(input[i] != '|') {
                if(input[i] == '_' || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
                    nato += input[i];
                i++;
            }
            i++;
            string team = "";
            while(input[i] != '|') {
                if(input[i] == '_' || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
                    team += input[i];
                i++;
            }

            int goals = 0;
            while(i < input.size()) {
                if(input[i] >= '0' && input[i] <= '9')
                    goals = goals * 10 + input[i] - '0';
                i++;
            }

            int aux = this->serv_list.RemovePlayer(name);
            if(aux == -1) {
                cout << "This player doesn't exists\n";
            }else cout << "The player was removed\n";
        }else if(option == 2) {
            print_player(this->serv_list);
        }else if(option == 3) {
            string nato;
            cin >> nato;
            DynamicArray player_list = this->serv_list.get_player_given_nato(nato);

            for(int i = 0; i < player_list.getLength(); i++) {
                cout << "Player name: " << player_list.getElem(i).getName() << '\n';
                cout << "Player nationality: " << player_list.getElem(i).getNationality() << '\n';
                cout << "Player team: " << player_list.getElem(i).getTeam() << '\n';
                cout << "Number of goals: " << player_list.getElem(i).getGoals() << '\n';
                cout << '\n';
            }
        }else break;
    }
}
