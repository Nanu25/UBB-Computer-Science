
#ifndef EVENTPLANNER_GUI_H
#define EVENTPLANNER_GUI_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Gui(Service& serv, std::string name, std::string location, bool organiser, QWidget *parent = nullptr);
    void setTitle();
    void populateList();
    void AddButtonHandler();
    void update() override;
    void populateComboBox();
    bool computeDist(std::string loc);
    void onCategoryChanged();
    void GoingButtonHandler();
    int getSelectedIndex();
    void HandlerChanged();
    ~Gui() override;

private:
    Ui::Gui *ui;
    Service& serv;
    std::string name, location;
    bool organiser;
    bool fr[100];
};


#endif //EVENTPLANNER_GUI_H
