
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include <QMessageBox>
#include "Gui.h"
#include "ui_Gui.h"


Gui::Gui(Service serv, QWidget *parent) :
        QWidget(parent), ui(new Ui::Gui), serv{serv} {
    ui->setupUi(this);
    populateList();
    QObject::connect(this->ui->ShowTaskButton, &QPushButton::clicked, this, &Gui::ShowTaskButtonHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    std::vector <Task> aux = this->serv.sort_by_pd();
    for(auto e : aux) {
        QString itemText = QString::fromStdString(e.toStr());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        if(e.getPriority() == 1) {
            QFont font;
            font.setBold(true);
            item->setFont(font);
        }
        this->ui->TaskWidget->addItem(item);
    }
}

void Gui::ShowTaskButtonHandler() {
    this->ui->FilteredWidget->clear();
    int priority = this->ui->PriorityLineEdit->text().toInt();
    std::vector <Task> aux = this->serv.filter_priority(priority);

    if(aux.size() == 0) {
        QMessageBox::warning(this, "No tasks found", "No task found");
        return;
    }

    int duration = 0;
    for(auto e : aux) {
        QString itemTitle = QString::fromStdString(e.toStr());
        QListWidgetItem *item = new QListWidgetItem(itemTitle);

        this->ui->FilteredWidget->addItem(item);
        duration += e.getDuration();
    }
    QString item = QString::fromStdString(std::to_string(duration));
    this->ui->FilteredWidget->addItem(item);
}
