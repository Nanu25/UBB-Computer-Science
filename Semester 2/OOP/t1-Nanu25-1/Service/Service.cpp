
#include "Service.h"

Service::Service(Repository &repo) : serv_list{repo}{

}

//Add a player to the list. If the player already exists then will return an error.
int Service::AddPlayer(TElement x) {
    int aux = this->serv_list.Add(x);
    return aux;
}

//Input: The player name.
//Output: Returns 1 if the player was removed or -1 if the players doesn't exist.
//The function search through repository and when it finds the player it will delete them.
int Service::RemovePlayer(std::string name) {
    int aux = this->serv_list.Remove(name);
    return aux;
}

Repository &Service::getrepo() {
    return this->serv_list;
}

//Input: The players list and the team i want to filter.
//Output: An array of players from the nationality from input sorted by goals.
//Make insertion sort to sort the players.
DynamicArray Service::get_player_given_nato(std::string nato) {
    DynamicArray players{1};

    for(int i = 0; i < this->serv_list.getLen(); i++)
        if(this->serv_list.getElement(i).getNationality() == nato)
            players.add(this->serv_list.getElement(i));

    //sort the players
    for(int i = 0; i < players.getLength(); i++) {
        for(int j = i; j < players.getLength(); j++)
            if(players.getElem(i).getGoals() > players.getElem(j).getGoals()) {
                TElement aux = players.getElem(i);
                players.setElement(i, players.getElem(j));
                players.setElement(j, aux);
            }
    }

    return players;
}

