//
// Created by alex_ on 6/25/2024.
//

#ifndef DELIVERNOW_GUI_H
#define DELIVERNOW_GUI_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Gui(Service& serv, std::string name, int coordX, int coordY, int rad, std::vector<std::string> streets, QWidget *parent = nullptr);
    void populateList();
    bool findStreet(std::string str);
    void setTitle();
    void AddButtonHandler();
    void DeliverButtonHandler();
    int getSelectedIndex();
    void populateComboBox();
    void onCategoryChanged();
    void update() override;
    ~Gui() override;

private:
    Ui::Gui *ui;
    Service& serv;
    std::string name;
    int coordX, coordY, rad;
    std::vector <std::string> streets;
};


#endif //DELIVERNOW_GUI_H
