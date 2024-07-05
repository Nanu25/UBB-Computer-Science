
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include "Gui.h"
#include "ui_Gui.h"


Gui::Gui(Service serv_list, QWidget *parent) : serv_list(serv_list),
        QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);
    this->populateList();

    QObject::connect(this->ui->SearchLineEdit, &QLineEdit::textChanged, this, &Gui::SearchLineHandler);
    QObject::connect(this->ui->ShowBestMatchingButton, &QPushButton::clicked, this, &Gui::BestMatchingButtonHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    this->ui->SearchEngineWidget->clear();
    std::vector<Document> aux = this->serv_list.sortName();
    for(auto e : aux) {
        QString itemText = QString::fromStdString(e.toStr());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        this->ui->SearchEngineWidget->addItem(item);
    }
}

void Gui::SearchLineHandler() {
    this->ui->SearchEngineWidget->clear();
    std::string s = this->ui->SearchLineEdit->text().toStdString();
    std::vector <Document> aux = this->serv_list.getFiltered(s);
    for(auto e : aux) {
        QString item = QString::fromStdString(e.toStr());
        this->ui->SearchEngineWidget->addItem(item);
    }
}

void Gui::BestMatchingButtonHandler() {
    std::string s = this->ui->SearchLineEdit->text().toStdString();
    std::string word = this->serv_list.getBestMatching(s);
    QString item = QString::fromStdString(word);
    this->ui->SearchEngineWidget->addItem(item);
}
