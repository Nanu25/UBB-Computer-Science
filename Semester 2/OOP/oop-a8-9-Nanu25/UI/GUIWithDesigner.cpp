//
// Created by alex_ on 5/16/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUIWithDesigner.h" resolved

#include <QAbstractButton>
#include <QMessageBox>
#include "GUIWithDesigner.h"
#include "ui_GUIWithDesigner.h"
#include "../Validator.h"

GUIWithDesigner::GUIWithDesigner(Service &serv, Service &user_list, QWidget *parent) : QWidget(parent), service{serv}, user_list{user_list}{
    ui.setupUi(this);
    //this->populateList();

    //current_movie_index = -1;
    QObject::connect(ui.addButton, &QPushButton::clicked, this, &GUIWithDesigner::addButtonHandler);
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, &GUIWithDesigner::deleteButtonHandler);
    QObject::connect(ui.updateButton, &QPushButton::clicked, this, &GUIWithDesigner:: updateButtonHandler);
    QObject::connect(ui.displayButton, &QPushButton::clicked, this, &GUIWithDesigner::displayButtonHandler);
//    QObject::connect(ui.filterButton, &QPushButton::clicked, this, &GUIWithDesigner::filterButtonHandler);
//    QObject::connect(ui.userWatchListButton, &QPushButton::clicked, this, &GUIWithDesigner::displayUserWLButtonHandler);
//    QObject::connect(ui.LikeButton, &QPushButton::clicked, this, &GUIWithDesigner::onLikeButtonClicked);
//    QObject::connect(ui.NextButton, &QPushButton::clicked, this, &GUIWithDesigner::onNextButtonClicked);
//    QObject::connect(ui.dislikeButton, &QPushButton::clicked, this, &GUIWithDesigner::onDislikeButtonClicked);
//    QObject::connect(ui.increaseLikesButton, &QPushButton::clicked, this, &GUIWithDesigner::increaseLikeButtonHandler);

}

GUIWithDesigner::~GUIWithDesigner() {
}

void GUIWithDesigner::addButtonHandler() {
    QString title = ui.TitleLineEdit->text();
    QString genre = ui.GenreLineEdit->text();
    int year = ui.YearLineEdit->text().toInt();
    int likes = ui.LikesLineEdit->text().toInt();
    QString trailer = ui.TrailerLineEdit->text();

    Movie newMovie{ title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString() };

    try {
        MovieValidator::validate(newMovie);
        this->service.Add_movie(newMovie); // Add the movie only if it passes validation
        this->populateList();
        //this->service.save_repo_file();

    }
    catch (ValidatorException& e) {

    }
}

void GUIWithDesigner::  populateList() {
    this->ui.MovieListWidget->clear();

    std::vector<Movie> movies = this->service.get_list().getRepo();
    for (const Movie &m: movies) {
        QString itemText = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " year: " + std::to_string(m.getYear()) + " likes: " +std::to_string(m.getLikes()) + " " + m.getTrailer());
        this->ui.MovieListWidget->addItem(itemText);
    }
}

void GUIWithDesigner::deleteButtonHandler() {
//    QString title = ui.TitleLineEdit->text();
//    try {
//        this->service.Remove_movie(title.toStdString());
//        this->populateList();
//        //this->serv.save_repo_file();
//
//    }
//    catch (const std::runtime_error& e) {
//
//    }

    int index = getSelectedIndex();
    if(index < 0) {
        QMessageBox::critical(this, "Error", "No movie");
        return;
    }

    Movie movie = this->service.get_list().getElement(index);
    this->service.Remove_movie(movie.getTitle());
    this->populateList();
}


void GUIWithDesigner::updateButtonHandler() {
    QString title = this->ui.TitleLineEdit->text();
    QString genre = this->ui.GenreLineEdit->text();
    int year = this->ui.YearLineEdit->text().toInt();
    int likes = this->ui.LikesLineEdit->text().toInt();
    QString trailer = this->ui.TrailerLineEdit->text();

    try {
        this->service.Update_movie(title.toStdString(), Movie{title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString()});
        this->populateList();
    }
    catch (const std::runtime_error& e) {

    }
    //this->serv.save_repo_file();
}

void GUIWithDesigner::displayButtonHandler() {
    this->populateList();
    this->service.save_repo_file();
}

int GUIWithDesigner::getSelectedIndex() {
    QModelIndexList selectedIndex = this->ui.MovieListWidget->selectionModel()->selectedIndexes();
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

//void GUIWithDesigner::displayUserWLButtonHandler() {
//    this->ui.UserListWidget->clear();
//
//    std::vector<Movie> movies = this->user_list.get_list().getRepo();
//    for (const Movie &m: movies) {
//        QString itemText = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " year: " + std::to_string(m.getYear()) + " likes: " +std::to_string(m.getLikes()) + " " + m.getTrailer());
//        this->ui.UserListWidget->addItem(itemText);
//    }
//}

//void GUIWithDesigner::filterButtonHandler() {
//    QString genre = this->ui.GenreLineEdit->text();
//    filtered_movie_list = this->service.get_movies_given_genre(genre.toStdString());
//    current_movie_index = 0;
//    iterationStopped = false;
//
//    if (!filtered_movie_list.empty()) {
//        showNextMovie();
//    } else {
//        this->ui.UserListWidget->clear();
//        this->ui.UserListWidget->addItem("No movies found for the given genre.");
//    }
//}
//
//void GUIWithDesigner::showNextMovie() {
//    if (!iterationStopped && current_movie_index < filtered_movie_list.size()) {
//        this->ui.UserListWidget->clear();
//        const auto& movie = filtered_movie_list[current_movie_index];
//        QString itemText = QString::fromStdString(movie.getTitle() + " - " + movie.getGenre() + " year: " + std::to_string(movie.getYear()) + " likes: " + std::to_string(movie.getLikes()) + " " + movie.getTrailer());
//        this->ui.UserListWidget->addItem(itemText);
//    } else if (iterationStopped && current_movie_index != -1) {
//        this->ui.UserListWidget->clear();
//        current_movie_index = -1;
//        this->ui.UserListWidget->addItem("Iteration stopped by user.");
//    }
//}
//
//void GUIWithDesigner::onLikeButtonClicked() {
//    if (current_movie_index < filtered_movie_list.size()) {
//        try {
//            user_list.Add_movie(filtered_movie_list[current_movie_index]);
//        } catch (const std::runtime_error& e) {
//        }
//        current_movie_index = (current_movie_index + 1) % filtered_movie_list.size();
//        showNextMovie();
//    }
//}
//
//void GUIWithDesigner::onNextButtonClicked() {
//    if (current_movie_index < filtered_movie_list.size()) {
//        current_movie_index = (current_movie_index + 1) % filtered_movie_list.size();
//        showNextMovie();
//    }
//}
//
//void GUIWithDesigner::onDislikeButtonClicked() {
//    iterationStopped = true;
//    showNextMovie();
//}
//
//void GUIWithDesigner::increaseLikeButtonHandler() {
//    QString title = this->ui.TitleLineEdit->text();
//    this->service.UpdateLikes(title.toStdString());
//    this->user_list.Remove_movie(title.toStdString());
//    this->displayUserWLButtonHandler();
//}
