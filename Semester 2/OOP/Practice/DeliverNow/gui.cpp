
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include <QMessageBox>
#include <fstream>
#include "gui.h"
#include "ui_Gui.h"


Gui::Gui(Service& serv, std::string name, int coordX, int coordY, int rad, std::vector<std::string> streets, QWidget *parent) :
serv{serv}, name{name}, coordX{coordX}, coordY{coordY}, rad{rad}, streets{streets},
        QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);
    this->populateComboBox();
    this->populateList();

    QPushButton::connect(this->ui->addButton, &QPushButton::clicked, this, &Gui::AddButtonHandler);
    QPushButton::connect(this->ui->deliverButton, &QPushButton::clicked, this, &Gui::DeliverButtonHandler);
    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, &Gui::onCategoryChanged);
}



Gui::~Gui() {
    delete ui;
}


void Gui::populateList() {
    std::string str = this->ui->comboBox->currentText().toStdString();

    if(this->name != "company") {
        this->ui->courierWidget->clear();
        for (auto e: this->serv.getServList().getPackageRepo()) {
            if ((e.getDelivery() == 0) && (findStreet(e.getStreet()) || (this->coordX + this->rad >= e.getLocX() &&
                                                                         this->coordY + this->rad >= e.getLocY())))
                this->ui->courierWidget->addItem(QString::fromStdString(
                        e.getRecipient() + " " + e.getStreet() + " " + std::to_string(e.getLocX()) + " " +
                        std::to_string(e.getLocY()) + " " + std::to_string(e.getDelivery())));
        }
    }else {
        this->ui->courierCompanyWidget->clear();
        for(auto e : this->serv.getServList().getPackageRepo()) {
            if(str == "All" || str == e.getStreet()) {
                QString itemtext = QString::fromStdString(
                        e.getRecipient() + " " + e.getStreet() + " " + std::to_string(e.getLocX()) + " " +
                        std::to_string(e.getLocY()) + " " + std::to_string(e.getDelivery()));
                QListWidgetItem *item = new QListWidgetItem(itemtext);
                if (e.getDelivery() == 1) {
                    item->setBackground(Qt::green);
                }
                this->ui->courierCompanyWidget->addItem(item);
            }
        }
    }
}

void Gui::setTitle() {
    this->setWindowTitle(QString::fromStdString(this->name + " " + std::to_string(this->coordX) + " " + std::to_string(this->coordY) + " " + std::to_string(this->rad)));
}

bool Gui::findStreet(std::string str) {
    for(auto e : this->streets)
        if(str == e)
            return 1;
    return 0;
}

void Gui::AddButtonHandler() {
    if(this->name != "company") {
        QMessageBox::warning(this, "error", "You must be a company!");
        return;
    }

    std::string recipient = this->ui->recipientLine->text().toStdString();
    std::string street = this->ui->streetLine->text().toStdString();
    int x = this->ui->xLine->text().toInt();
    int y= this->ui->yLine->text().toInt();

    this->serv.addPackage(Package{recipient, street, x, y, 0});
    this->populateList();
}

void Gui::update() {
    this->populateList();
    this->populateComboBox();
    std::ofstream fout("../package.txt");
    for(auto e : this->serv.getServList().getPackageRepo())
        fout << e.getRecipient() << "," << e.getStreet() << "," << e.getLocX() << "," << e.getLocY() << "," << e.getDelivery() << '\n';
    fout.close();
}

void Gui::DeliverButtonHandler() {
    int index = this->getSelectedIndex();
    this->serv.getServList().getPackageRepo()[index].setDelivery();
    this->serv.notify();
}

int Gui::getSelectedIndex() {
    QModelIndexList list = this->ui->courierWidget->selectionModel()->selectedIndexes();
    if(list.empty()) {
        return -1;
    }

    int index = list.at(0).row();
    return index;
}

void Gui::populateComboBox() {
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("All");
    for(auto e : this->serv.getStreets())
        this->ui->comboBox->addItem(QString::fromStdString(e));
}

void Gui::onCategoryChanged() {
    this->populateList();
}

