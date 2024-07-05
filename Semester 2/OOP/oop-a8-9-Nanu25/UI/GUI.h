#pragma once
#include <qwidget.h>
//#include "Service.h"
#include "../Service/Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget
{
private:
    Service& serv;

    QListWidget* moviesListWidget;
    QLineEdit* title;
    QLineEdit* genre;
    QLineEdit* year;
    QLineEdit* likes;
    QLineEdit* trailer;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* printButton;
public:
    GUI(Service& serv);

private:
    void buildGUI();
    void populateList();

    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void printButtonHandler();
};

