
#include <fstream>
#include "Repository.h"

void Repository::addUser(User u) {
    this->user_repo.push_back(u);
}

void Repository::addItem(Item i) {
    this->item_repo.push_back(i);
}

std::vector<Item> &Repository::getItemRepo() {
    return this->item_repo;
}

void Repository::readFile() {
    std::ifstream fin("../user.txt");
    std::string name, type;
    int id;
    while(fin >> name >> id >> type) {
        this->user_repo.push_back(User{name, id, type});
    }

    fin.close();

    std::ifstream f("../item.txt");
    name = "";
    std::string category, line;
    int price;
    while(std::getline(f, line)) {
        int index = 0;
        name = "";
        while(line[index] != ',')
            name += line[index++];
        index++;

        category = "";
        while(line[index] != ',')
            category += line[index++];
        index++;

        price = 0;
        while(line[index] != ',')
            price = price * 10 + line[index++] - '0';
        index++;

        Item i{name, category, price};
        //I can have more offerts.
        while(index < line.size()) {
            int id = 0;
            while(line[index] != ',')
                id = id * 10 + line[index++] - '0';
            index++;

            std::string date = "";
            while(line[index] != ',')
                date += line[index++];
            index++;

            int sum = 0;
            while(index < line.size() && line[index] != ',') {
                sum = sum * 10 + line[index++] - '0';
            }
            index++;
            std::tuple<int, std::string, int> d{id, date, sum};
            i.addOffert(d);
        }

        this->item_repo.push_back(i);
    }

    f.close();
}

std::vector<User> &Repository::getUserRepo() {
    return this->user_repo;
}

void Repository::writeFile() {
    std::ofstream g("../item.txt");
    for(auto e : this->item_repo) {
        g << e.getName() << "," << e.getCategory() << "," << e.getPrice() << ",";
        for(auto it : e.getOfferts())
            g << std::get<0>(it) << "," << std::get<1>(it) << "," << std::get<2>(it) <<",";
        g << '\n';
    }
    g.close();
}


