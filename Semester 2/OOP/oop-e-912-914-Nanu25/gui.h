//
// Created by alex_ on 6/27/2024.
//

#ifndef OOP_E_912_914_NANU25_GUI_H
#define OOP_E_912_914_NANU25_GUI_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Gui(Service& serv, std::string  name, std::string  position, QWidget *parent = nullptr);
    void populateList();
    void setTitle();
    void AddButtonHandler();
    void SaveAllButtonHandler();
    void AcceptHandler();
    int getSelectedIndex();
    void SaveButtonHandler();
    void DevelopButtonHandler();
    int getSelectedIndexList();
    void update() override;
    ~Gui() override;

private:
    Ui::Gui *ui;
    Service& serv;
    std::string name, position;
};

#endif //OOP_E_912_914_NANU25_GUI_H
