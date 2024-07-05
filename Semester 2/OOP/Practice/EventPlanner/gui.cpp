
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include <QMessageBox>
#include <fstream>
#include "gui.h"
#include "ui_Gui.h"


Gui::Gui(Service& serv, std::string name, std::string location, bool organiser, QWidget *parent) : serv{serv}, name{name}, location(location), organiser{organiser},
        QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);

    this->populateList();
    this->populateComboBox();

    std::ofstream g("../a.txt");
    for(auto e : this->serv.getService().getEventRepo()) {
        g << e.getOrganiser() << " " << e.getEventName() << " " << e.getDescription() << " " << e.getEventLocation() << " " << e.getDate() << '\n';
    }
    g.close();

    QPushButton::connect(this->ui->addButton, &QPushButton::clicked, this, &Gui::AddButtonHandler);
    connect(this->ui->comboBox, &QComboBox::currentTextChanged, this, &Gui::onCategoryChanged);
    QPushButton::connect(this->ui->GoingButton, &QPushButton::clicked, this, &Gui::GoingButtonHandler);
    connect(this->ui->EventWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Gui::HandlerChanged);
}

Gui::~Gui() {

    delete ui;
}

void Gui::setTitle() {
    this->setWindowTitle(QString::fromStdString(this->name + " " + this->location));
}

void Gui::populateList() {
    this->ui->EventWidget->clear();

    std::string combotext = this->ui->comboBox->currentText().toStdString();
    for(auto e : this->serv.getService().getEventRepo()) {
        if(combotext == "All" || this->computeDist(e.getEventLocation()) == 1) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(
                    e.getOrganiser() + " " + e.getEventName() + " " + e.getEventLocation() + " " + e.getDate()));
            if (e.getOrganiser() == this->name)
                item->setBackground(Qt::green);
            this->ui->EventWidget->addItem(item);
        }
    }
}

int Gui::getSelectedIndex() {
    QModelIndexList list = this->ui->EventWidget->selectionModel()->selectedIndexes();
    if(list.size() == 0) {
        return -1;
    }

    int index = list.at(0).row();
    return index;

}

void Gui::AddButtonHandler() {
    if(this->organiser == 0) {
        QMessageBox::warning(this, "error", "you must be an organiser");
        return;
    }

    std::string nm = this->ui->nameLine->text().toStdString();
    std::string desc = this->ui->descriptionLine->text().toStdString();
    std::string loc = this->ui->locationLine->text().toStdString();
    std::string date = this->ui->dateLine->text().toStdString();

    try {
        this->serv.AddEvent(Event{this->name, nm, desc, loc, date});
        this->serv.sortDate();
        this->populateList();
        this->serv.notify();
    }catch (std::runtime_error& re) {
        QMessageBox::warning(this, "Error", re.what());
    }
}

void Gui::update() {
    this->populateList();
    this->populateComboBox();

    std::ofstream g("../a.txt");
    for(auto e : this->serv.getService().getEventRepo()) {
        g << e.getOrganiser() << " " << e.getEventName() << " " << e.getDescription() << " " << e.getEventLocation() << " " << e.getDate() << '\n';
    }
    g.close();
}

void Gui::populateComboBox() {
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("All");
    this->ui->comboBox->addItem("Interesed");

    this->populateList();
}

bool Gui::computeDist(std::string loc) {
    int x = 0;
    int index = 0;
    while(this->location[index] != ' ')
        x = x * 10 + this->location[index++];
    index++;

    int y = 0;
    while(index < this->location.size())
        y = y * 10 + this->location[index++];

    int curx = 0;
    index = 0;
    while(loc[index] != ' ')
        curx = curx * 10 + loc[index++];
    index++;

    int cury = 0;
    while(index < this->location.size())
        cury = cury * 10 + this->location[index++];

    return abs(x  - curx) <= 5 && abs(y - cury) <= 5;
}

void Gui::onCategoryChanged() {
    this->populateList();
}

void Gui::GoingButtonHandler() {
    int index = getSelectedIndex();
    if(fr[index] == 1) {
        QMessageBox::warning(this, "Error", "You already go to this event");
    }else fr[index] = 1;
}



void Gui::HandlerChanged() {
    int index = getSelectedIndex();
    QMessageBox::information(this, "Info", QString::fromStdString(this->serv.getService().getEventRepo()[index].getDescription()));
    if(this->organiser == 1) {

    }

}
