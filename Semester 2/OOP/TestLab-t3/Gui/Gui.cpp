
// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved

#include "Gui.h"
#include "ui_Gui.h"


Gui::Gui(Service serv_list, QWidget *parent) : serv_list{serv_list},
        QWidget(parent), ui(new Ui::Gui) {
    ui->setupUi(this);

    populateList();
    QObject::connect(this->ui->AddButton, &QPushButton::clicked, this, &Gui::AddButtonHandler);
    QObject::connect(this->ui->ComputeSolutionButton, &QPushButton::clicked, this, &Gui::ComputeSolutionButtonHandler);
}

Gui::~Gui() {
    delete ui;
}

void Gui::populateList() {
    this->ui->EquationWidget->clear();

    std::vector<Equation> aux = this->serv_list.getList().getRepo();
    for(auto e : aux) {
        QString itemtext = QString::fromStdString(e.toStr());
        QListWidgetItem* item = new QListWidgetItem(itemtext);
        if(e.getDiscriminant() < 0) {
            item->setBackground(Qt::green);
        }
        this->ui->EquationWidget->addItem(item);
    }
}

void Gui::AddButtonHandler() {
    double a = this->ui->ALineEdit->text().toDouble();
    double b = this->ui->BLineEdit->text().toDouble();
    double c = this->ui->CLineEdit->text().toDouble();

    this->serv_list.AddEquation(Equation(a, b, c));
    this->populateList();
}

int Gui::getSelectedIndex() {
    QModelIndexList selectedindex = this->ui->EquationWidget->selectionModel()->selectedIndexes();
    int index = selectedindex.at(0).row();
    return index;
}

std::string cts(std::complex<double> c) {
    std::ostringstream ss;
    if (c.imag() == 0) {
        ss << c.real();
    } else {
        ss << c;
    }
    return ss.str();
}

void Gui::ComputeSolutionButtonHandler() {
    int index = getSelectedIndex();
    std::vector<std::complex<double>> aux = this->serv_list.solve(index);
    QString solutionText;
    for (int i = 0; i < aux.size(); i++) {
        solutionText += QString::fromStdString(cts(aux[i]));
        if (i != aux.size() - 1) {
            solutionText += ", ";
        }
    }

    this->ui->SolutionLine->setText(solutionText);
}
