
#ifndef ARTACTION_ITEM_H
#define ARTACTION_ITEM_H


#include <string>
#include <vector>

class Item {
private:
    std::string name, category;
    int price;
    std::vector<std::tuple<int, std::string, int>> offerts;
public:
    Item(std::string name, std::string category, int price);
    int getPrice();
    std::string getName();
    std::string getCategory();
    std::vector<std::tuple<int, std::string, int>> getOfferts();
    void addOffert(std::tuple<int, std::string, int> elem);
    void setPrice(int price);

    std::string toString();

};


#endif //ARTACTION_ITEM_H
