//
// Created by alex_ on 5/16/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUIWithDesigner.h" resolved

#include <QAbstractButton>
#include <QMessageBox>
#include <QStandardItemModel>
#include "GUIWithDesigner.h"
#include "ui_GUIWithDesigner.h"
#include "../Validator.h"
#include <QShortcut>
#include <QKeySequence>

GUIWithDesigner::GUIWithDesigner(Service &serv, Service &user_list, QWidget *parent) : QWidget(parent), service{serv}, user_list{user_list}{
    ui.setupUi(this);
    this->populateList();
    this->undoRedo.add_undo(this->service);
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &GUIWithDesigner::addButtonHandler);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &GUIWithDesigner::deleteButtonHandler);
    QObject::connect(ui.updateButton, &QPushButton::clicked, this, &GUIWithDesigner:: updateButtonHandler);
    QObject::connect(ui.displayButton, &QPushButton::clicked, this, &GUIWithDesigner::displayButtonHandler);
    QObject::connect(ui.UndoButton, &QPushButton::clicked, this, &GUIWithDesigner::undoButtonHandler);
    QObject::connect(ui.RedoButton, &QPushButton::clicked, this, &GUIWithDesigner::redoButtonHandler);

    QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QObject::connect(undoShortcut, &QShortcut::activated, this, &GUIWithDesigner::undoButtonHandler);

    QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    QObject::connect(redoShortcut, &QShortcut::activated, this, &GUIWithDesigner::redoButtonHandler);
}

GUIWithDesigner::~GUIWithDesigner() {
}
void GUIWithDesigner::addButtonHandler() {
    QString title = ui.TitleLineEdit->text();
    QString genre = ui.GenreLineEdit->text();
    int year = ui.YearLineEdit->text().toInt();
    int likes = ui.LikesLineEdit->text().toInt();
    QString trailer = ui.TrailerLineEdit->text();

    Movie newMovie{title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString()};

    try {
        MovieValidator::validate(newMovie);
        this->service.Add_movie(newMovie); // Add the movie only if it passes validation
        this->undoRedo.add_undo(this->service); // Add current state to undo list
        this->service.notify();

//        this->populateList();
    } catch (ValidatorException& e) {
        QMessageBox::critical(this, "Validation Error", "Error");
    }
}


void GUIWithDesigner::populateList() {
    // Clear the existing model from the QTableView
    QStandardItemModel* model = new QStandardItemModel(this);
    QStringList headers = {"Title", "Genre", "Year", "Likes", "Trailer"};
    model->setHorizontalHeaderLabels(headers);

    // Retrieve the list of movies
    std::vector<Movie> movies = this->service.get_list().getRepo();

    // Populate the model with the movie data
    for (const Movie& m : movies) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::fromStdString(m.getTitle())));
        row.append(new QStandardItem(QString::fromStdString(m.getGenre())));
        row.append(new QStandardItem(QString::number(m.getYear())));
        row.append(new QStandardItem(QString::number(m.getLikes())));
        row.append(new QStandardItem(QString::fromStdString(m.getTrailer())));
        model->appendRow(row);
    }

    // Set the model to the QTableView
    this->ui.AdministratorTable->setModel(model);
}


void GUIWithDesigner::deleteButtonHandler() {
    int index = getSelectedIndex();
    if(index < 0) {
        QMessageBox::critical(this, "Error", "No movie selected");
        return;
    }

    Movie movie = this->service.get_list().getElement(index);
    this->service.Remove_movie(movie.getTitle());
    this->undoRedo.add_undo(this->service); // Add current state to undo list
    this->service.notify();

//    this->populateList();
}


void GUIWithDesigner::updateButtonHandler() {
    QString title = this->ui.TitleLineEdit->text();
    QString genre = this->ui.GenreLineEdit->text();
    int year = this->ui.YearLineEdit->text().toInt();
    int likes = this->ui.LikesLineEdit->text().toInt();
    QString trailer = this->ui.TrailerLineEdit->text();

    try {
        this->service.Update_movie(title.toStdString(), Movie{title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString()});
        this->undoRedo.add_undo(this->service); // Add current state to undo list
        this->service.notify();
//        this->populateList();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Update Error", e.what());
    }
}

void GUIWithDesigner::displayButtonHandler() {
    this->populateList();
    //this->service.save_repo_file();
}

int GUIWithDesigner::getSelectedIndex() {
    QModelIndexList selectedIndex = this->ui.AdministratorTable->selectionModel()->selectedIndexes();
    if(selectedIndex.size() == 0) {
        this->ui.TitleLineEdit->clear();
        this->ui.GenreLineEdit->clear();
        this->ui.YearLineEdit->clear();
        this->ui.LikesLineEdit->clear();
        this->ui.TrailerLineEdit->clear();
        return -1;
    }

    int index = selectedIndex.at(0).row();
    return index;
}

void GUIWithDesigner::undoButtonHandler() {
    try {

        Service aux = this->undoRedo.make_undo();

        this->service = aux; // Restore prev state
        this->populateList();
    } catch (const std::out_of_range& e) {
        QMessageBox::critical(this, "Undo Error", e.what());
    }
}

void GUIWithDesigner::redoButtonHandler() {
    try {
        Service aux = this->undoRedo.make_redo();
        this->service = aux; // Restore next state
        this->service.notify();

//        this->populateList();
    } catch (const std::out_of_range& e) {
        QMessageBox::critical(this, "Redo Error", e.what());
    }
}

void GUIWithDesigner::setTitle() {
    this->setWindowTitle("Administrator");
}

void GUIWithDesigner::update() {
    this->populateList();
}
