
#ifndef ARTACTION_GUI_H
#define ARTACTION_GUI_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer{
Q_OBJECT

public:
    explicit GUI(Service& serv, std::string name, std::string type, int id, QWidget *parent = nullptr);

    ~GUI() override;

    void populateList();
    void setTitle();
    void populateCombo();
    void onCategoryChanged(const QString& category);
    void AddButtonHandler();
    int getSelectedIndex();
    void showOffertsHandler();
    void BidButtonHandler();
    void update() override;

private:
    Ui::GUI *ui;
    Service& serv;
    std::string name, type;
    int id;
};


#endif //ARTACTION_GUI_H
