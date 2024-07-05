
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include "Gui.h"
#include "ui_Gui.h"


Gui::Gui(Service serv, QWidget *parent) :
        QWidget(parent), ui(new Ui::Gui), serv{serv} {
    ui->setupUi(this);
    this->populateList();

    QObject::connect(this->ui->ShowItemsButton, &QPushButton::clicked, this, &Gui::ShowItemsButtonHandler);

    QObject::connect(this->ui->FilterLineEdit, &QLineEdit::textChanged, this, &Gui::filterListHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    this->ui->ShoppingWidget->clear();

    std::vector <Product> aux = this->serv.sort_by_category_name();
    for(auto e : aux) {
        QString item = QString::fromStdString(e.toStr());
        QListWidgetItem* i = new QListWidgetItem(item);
        this->ui->ShoppingWidget->addItem(i);
    }
}

void Gui::ShowItemsButtonHandler() {
    this->ui->FilterWidget->clear();
    std::string category = this->ui->CategoryLineEdit->text().toStdString();
    std::vector <Product> aux = this->serv.filter_category(category);
    for(auto e : aux) {
        QString item = QString::fromStdString(e.toStr());
        QListWidgetItem* i = new QListWidgetItem(item);
        this->ui->FilterWidget->addItem(i);
    }
}

void Gui::filterListHandler() {
    this->ui->ShoppingWidget->clear();
    std::string s = this->ui->FilterLineEdit->text().toStdString();
    std::vector <Product> aux = this->serv.filter_by_name(s);

    for(auto e : aux) {
        QString item = QString::fromStdString(e.toStr());
        this->ui->ShoppingWidget->addItem(item);
    }
}
