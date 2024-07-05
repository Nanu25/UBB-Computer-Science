
#ifndef TESTPROFA_GUI_H
#define TESTPROFA_GUI_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer {
    Q_OBJECT

public:
    explicit GUI(Service& serv, std::string name, std::string type,  QWidget *parent = nullptr);
    void update() override;
    ~GUI() override;
    void populateList();
    void setTitle(std::string name);
    void AddButtonHandler();
    void RemoveButtonHandler();
    void ResolveButtonHandler();

    int getSelectedIndex();

private:
    Ui::GUI *ui;
    Service& serv_list;
    std::string name, type;
};


#endif //TESTPROFA_GUI_H
