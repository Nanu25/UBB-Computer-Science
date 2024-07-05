
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include <QStandardItemModel>
#include <QtWidgets>
#include <QComboBox>
#include <fstream>
#include <iostream>
#include "gui.h"
#include "ui_Gui.h"

Gui::Gui(Service& serv, std::string  name, std::string  position,QWidget *parent) : serv{serv}, name{name}, position{position},
                                                                                    QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);
    this->populateList();

    QPushButton::connect(this->ui->addButton, &QPushButton::clicked, this, &Gui::AddButtonHandler);
    QPushButton::connect(this->ui->SaveAllButton, &QPushButton::clicked, this, &Gui::SaveAllButtonHandler);
    QPushButton::connect(this->ui->saveButton, &QPushButton::clicked, this, &Gui::SaveButtonHandler);
    QPushButton::connect(this->ui->developButton, &QPushButton::clicked, this, &Gui::DevelopButtonHandler);
    connect(this->ui->IdeeaTableView, &QTableView::doubleClicked, this, &Gui::AcceptHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Title", "Status", "Creator", "Year"});

    auto ideas = serv.getServIdeea().getIdeeaRepo();

    for(auto e : ideas) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(e.getTitle()));
        row << new QStandardItem(QString::fromStdString(e.getStatus()));
        row << new QStandardItem(QString::fromStdString(e.getCreator()));
        row << new QStandardItem(QString::number(e.getYear()));

        model->appendRow(row);
    }

    this->ui->IdeeaTableView->setModel(model);
}

void Gui::setTitle() {
    this->setWindowTitle(QString::fromStdString(this->name + " " + this->position));
}

void Gui::AddButtonHandler() {
    std::string title = this->ui->titleLineEdit->text().toStdString();
    std::string description = this->ui->descriptionLineEdit->text().toStdString();
    std::string status = "proposed";
    std::string creator = this->name;
    int nr = this->ui->durationLineEdit->text().toInt();

    if(title == "" || (nr > 3 || nr < 1)) {
        QMessageBox::warning(this, "error", "Invalid input");
        return;
    }

    this->serv.AddIdeeaServ(Ideea{title, description, status, creator, nr});
    this->serv.sortDuration();
    this->serv.notify();
}

void Gui::SaveAllButtonHandler() {
    if(this->position != "senior") {
        QMessageBox::warning(this, "error", "you must be a senior");
        return;
    }

    std::ofstream g("../a.txt");
    for(auto e : this->serv.getServIdeea().getIdeeaRepo()) {
        if(e.getStatus() == "accepted")
            g << e.getTitle() << " (" << e.getCreator() << ") " << e.getYear() << " " << e.getDescription() << '\n';
    }
    g.close();
}

void Gui::AcceptHandler() {
    if(this->position != "senior") {
        QMessageBox::warning(this, "error", "you must be a senior");
        return;
    }

    int index = this->getSelectedIndex();

    if( this->serv.getServIdeea().getIdeeaRepo()[index].getStatus() == "accepted") {
        QMessageBox::warning(this, "error", "The ideea must to pe proposed.");
        return;
    }

    this->serv.getServIdeea().getIdeeaRepo()[index].setStatus("accepted");
    this->serv.notify();
}

int Gui::getSelectedIndex() {
    QModelIndexList selectedindex = this->ui->IdeeaTableView->selectionModel()->selectedIndexes();
    if (selectedindex.empty()) {
        return -1;
    }
    int index = selectedindex.at(0).row();
    return index;
}

void Gui::SaveButtonHandler() {
    int index = this->getSelectedIndexList();

    std::string desc = this->ui->descriptionLineEdit->text().toStdString();


    std::vector<Ideea> aux = this->serv.getAcceptedIdeeas(this->name);
    if(desc != "") {
        aux[index].setDescription(desc);
        this->serv.ChangeDescription(aux[index].getTitle(), aux[index].getCreator(), desc);
    }
    auto e = aux[index];
    std::ofstream g(e.getTitle());
    g << e.getTitle()  << " " << e.getDescription() << " " << e.getStatus() << " " << e.getCreator() << " " << e.getYear();
    g.close();
}

void Gui::DevelopButtonHandler() {
    std::vector<Ideea> aux = this->serv.getAcceptedIdeeas(this->name);
    if(aux.size() == 0) {
        QMessageBox::warning(this, "error", "You have no ideas");
        return;
    }

    this->ui->IdeeaWidget->clear();
    for(auto e : aux)
        this->ui->IdeeaWidget->addItem(QString::fromStdString(e.getTitle() + " " + e.getDescription() + " " + e.getStatus() + " " + e.getCreator() + " " + std::to_string(e.getYear())));

}

int Gui::getSelectedIndexList() {
    QModelIndexList list = this->ui->IdeeaWidget->selectionModel()->selectedIndexes();
    if(list.empty())
        return -1;
    int index = list.at(0).row();
    return index;
}

void Gui::update() {
    this->populateList();
}


