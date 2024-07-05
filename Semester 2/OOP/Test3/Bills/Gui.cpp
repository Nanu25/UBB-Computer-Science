//
// Created by alex_ on 5/27/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include <iostream>
#include <QMessageBox>
#include "Gui.h"
#include "ui_Gui.h"


Gui::Gui(Service serv_list, QWidget *parent) : serv_list{serv_list},
        QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);

    this->populateList();

    QObject::connect(this->ui->pairLineEdit, &QLineEdit::textChanged, this, &Gui::PaidLineHandler);
    QObject::connect(this->ui->CalculateTotalButton, &QPushButton::clicked, this, &Gui::ComputeTotalButtonHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    this->ui->listWidget->clear();
    std::vector <Bills> aux = this->serv_list.sort_by_company();
    for(auto e : aux) {
        QString itemText = QString::fromStdString(e.toStr());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        if(e.getPaid() == "false") {
            item->setBackground(Qt::red);
        }
        this->ui->listWidget->addItem(item);
    }
}

void Gui::PaidLineHandler() {
    this->ui->listWidget->clear();
    std::string s = this->ui->pairLineEdit->text().toStdString();
    std::vector <Bills> aux = this->serv_list.filter_paid_unpaid(s);

    for(auto e : aux) {
        QString itemText = QString::fromStdString(e.toStr());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        if(e.getPaid() == "false")
            item->setBackground(Qt::red);
        this->ui->listWidget->addItem(item);
    }
}

void Gui::ComputeTotalButtonHandler() {
    std::string s = this->ui->CompanyLineEdit->text().toStdString();
    std::vector <Bills> aux = this->serv_list.filter_company_name(s);

    float total = 0;
    for(auto e : aux) {
        total += e.getCost();
    }

    if(total == 0) {
        QMessageBox::warning(NULL, "Error", "This company doesn't exists");
        return;
    }

    this->ui->TotalCost->setText(QString::fromStdString(std::to_string(total)));
}
