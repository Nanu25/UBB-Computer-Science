
#ifndef SEARCHENGINE_GUI_H
#define SEARCHENGINE_GUI_H

#include <QWidget>
#include "../Service/Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QWidget {
Q_OBJECT

public:
    explicit Gui(Service serv_list, QWidget *parent = nullptr);

    ~Gui() override;

private:
    Ui::Gui *ui;
    Service serv_list;
    void populateList();
    void SearchLineHandler();
    void BestMatchingButtonHandler();
};


#endif //SEARCHENGINE_GUI_H
