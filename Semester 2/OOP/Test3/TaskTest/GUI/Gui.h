#pragma once
#include <QWidget>
#include "../Service/Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QWidget {
Q_OBJECT

public:
    explicit Gui(Service serv, QWidget *parent = nullptr);

    ~Gui() override;


private:
    Ui::Gui *ui;
    Service serv;

    void populateList();
    void ShowTaskButtonHandler();

};


