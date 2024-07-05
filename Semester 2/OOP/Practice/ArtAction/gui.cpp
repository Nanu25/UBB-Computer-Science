
// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include <QMessageBox>
#include <QMargins>
#include <iostream>
#include <fstream>
#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(Service& serv, std::string name, std::string type, int id, QWidget *parent) :
        serv{serv}, QWidget(parent), ui(new Ui::GUI), name(name), type(type), id(id) {
    ui->setupUi(this);
    this->populateCombo();
    this->populateList();

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &GUI::onCategoryChanged);
    QPushButton::connect(this->ui->addButton, &QPushButton::clicked, this, &GUI::AddButtonHandler);
    connect(ui->ItemWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &GUI::showOffertsHandler);
    QPushButton::connect(this->ui->BidButton, &QPushButton::clicked, this, &GUI::BidButtonHandler);
}


GUI::~GUI() {
    delete ui;
}

void GUI::populateList() {
    this->ui->ItemWidget->clear();

    QString selectedCategory = ui->comboBox->currentText();

    for (auto e : this->serv.getServiceItem().getItemRepo()) {
        if (QString::fromStdString(e.getCategory()) == selectedCategory || selectedCategory == "All") {
            this->ui->ItemWidget->addItem(QString::fromStdString(e.toString()));
        }
    }
}

void GUI::setTitle() {
    this->setWindowTitle(QString::fromStdString(this->name));
}

void GUI::populateCombo() {
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("All");

    for (auto& e : this->serv.getAllCategories()) {
        this->ui->comboBox->addItem(QString::fromStdString(e));
    }
}

    void GUI::onCategoryChanged(const QString& category) {
        this->populateList();
    }

void GUI::AddButtonHandler() {
    std::string  name = this->ui->nameLineEdit->text().toStdString();
    std::string category = this->ui->categoryLineEdit->text().toStdString();
    int price = this->ui->priceLineEdit->text().toInt();

    if(this->type != "administrator") {
        QMessageBox::warning(this, "Error", " You must be an administrato");
        return;
    }

    if(price <= 0 || name == "") {
        QMessageBox::warning(this, "Error", "Inavlid input");
        return;
    }


    this->serv.addItem(Item{name, category, price});
    populateList();
    populateCombo();
    this->serv.saveFileRepo();

}

void GUI::update() {
    this->populateList();
    this->populateCombo();
}

int GUI::getSelectedIndex() {
    QModelIndexList selectedindex =this->ui->ItemWidget->selectionModel()->selectedIndexes();
    if (selectedindex.empty()) {
        return -1;
    }
    int index = selectedindex.at(0).row();
    return index;
}

void GUI::showOffertsHandler() {
    this->ui->OffertsWirget->clear();
    int index = getSelectedIndex();
    Item i1 = this->serv.getServiceItem().getItemRepo()[index];
    auto offers = i1.getOfferts();

    auto comparator = [](const auto& lhs, const auto& rhs) {
        return std::get<1>(lhs) > std::get<1>(rhs);
    };
    std::sort(offers.begin(), offers.end(), comparator);
    for(auto e : offers) {
        this->ui->OffertsWirget->addItem(QString::fromStdString(std::to_string(std::get<0>(e)) + " " + std::get<1>(e) + " " + std::to_string(std::get<2>(e))));
    }
}

void GUI::BidButtonHandler() {
    if(this->type != "collector") {
        QMessageBox::warning(this, "Error", "You must be a collector");
        return;
    }

    int index = getSelectedIndex();
    int sum = this->ui->BidLineEdit->text().toInt();
    Item i1 = this->serv.getServiceItem().getItemRepo()[index];

    if(i1.getPrice() > sum) {
        QMessageBox::warning(this, "Error", "You need a bigger bid!");
        return;
    }

    this->serv.getServiceItem().getItemRepo()[index].setPrice(sum);
    this->serv.getServiceItem().getItemRepo()[index].addOffert(std::tuple(this->id, "2024/6/27", sum));
    populateList();
    this->serv.notify();
    this->serv.saveFileRepo();
}
