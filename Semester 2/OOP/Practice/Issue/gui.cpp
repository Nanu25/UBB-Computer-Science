
#include <QMessageBox>
#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(Service& serv, std::string name, std::string type, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), serv_list{serv}, name(name), type(type) {
    ui->setupUi(this);
    this->populateList();

    QPushButton::connect(this->ui->AddButton, &QPushButton::clicked, this, &GUI::AddButtonHandler);
    QPushButton::connect(this->ui->RemoveButton, &QPushButton::clicked, this, &GUI::RemoveButtonHandler);
    QPushButton::connect(this->ui->ResolveButton, &QPushButton::clicked, this, &GUI::ResolveButtonHandler);
}

GUI::~GUI() {
    delete ui;
}

void GUI::update() {
    this->populateList();
}

void GUI::populateList() {
    this->ui->IssueWidget->clear();
    std::vector <Issue> aux = this->serv_list.sortIssue();
    for(auto e : aux) {
        QString itemTexxt = QString::fromStdString(e.toString());
        this->ui->IssueWidget->addItem(itemTexxt);
    }
}

void GUI::setTitle(std::string name) {
    this->setWindowTitle(QString::fromStdString(name));
}

void GUI::AddButtonHandler() {
    if(this->type == "tester") {
        std::string description = this->ui->IssueLine->text().toStdString();

        // Check if the description is empty
        if (description.empty()) {
            QMessageBox::warning(this, "Input Error", "Please insert at least one character.");
            return;
        }

        try {
            this->serv_list.AddIssue(Issue{description, "open", this->name, ""});
            this->populateList();
        } catch (const std::runtime_error &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }else QMessageBox::warning(this, "Error", "You must be a tester");
}

void GUI::RemoveButtonHandler() {
    std::string desc = this->ui->IssueLine->text().toStdString();
    try {
        this->serv_list.RemoveIssue(desc);
        this->populateList();
    }catch (std::runtime_error &e) {
        QMessageBox::warning(this, "Error", "Can t remove this task");
    }
}

void GUI::ResolveButtonHandler() {
    if(this->type == "programmer") {
        int index = getSelectedIndex();
        try {
            this->serv_list.ResolveIssue(index, this->name);
            populateList();
        }catch (std::runtime_error &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }else {
        QMessageBox::warning(this, "Error", "You must pe a programmer to resolve");
    }
}

int GUI::   getSelectedIndex() {
    QModelIndexList selectedindex = this->ui->IssueWidget->selectionModel()->selectedIndexes();
    int index = selectedindex.at(0).row();
    return index;
}
