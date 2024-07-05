//
// Created by alex_ on 5/20/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI_USER.h" resolved

#include "gui_user.h"
#include "ui_GUI_USER.h"


GUI_USER::GUI_USER(Service service, Service serv, QWidget *parent) : service{service}, user_list{serv}, QWidget(parent) {
    ui.setupUi(this);

    current_movie_index = -1;
    QObject::connect(ui.filterButton, &QPushButton::clicked, this, &GUI_USER::filterButtonHandler);
    QObject::connect(ui.userWatchListButton, &QPushButton::clicked, this, &GUI_USER::displayUserWLButtonHandler);
    QObject::connect(ui.LikeButton, &QPushButton::clicked, this, &GUI_USER::onLikeButtonClicked);
    QObject::connect(ui.NextButton, &QPushButton::clicked, this, &GUI_USER::onNextButtonClicked);
    QObject::connect(ui.dislikeButton, &QPushButton::clicked, this, &GUI_USER::onDislikeButtonClicked);
    QObject::connect(ui.increaseLikeButton, &QPushButton::clicked, this, &GUI_USER::increaseLikeButtonHandler);

}

GUI_USER::~GUI_USER() {
    //delete ui;
}


void GUI_USER::displayUserWLButtonHandler() {
    this->ui.UserListWidget->clear();

    std::vector<Movie> movies = this->user_list.get_list().getRepo();
    for (const Movie &m: movies) {
        QString itemText = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " year: " + std::to_string(m.getYear()) + " likes: " +std::to_string(m.getLikes()) + " " + m.getTrailer());
        this->ui.UserListWidget->addItem(itemText);
    }
}

void GUI_USER::filterButtonHandler() {
    QString genre = this->ui.GenreLineEdit->text();
    filtered_movie_list = this->service.get_movies_given_genre(genre.toStdString());
    current_movie_index = 0;
    iterationStopped = false;

    if (!filtered_movie_list.empty()) {
        showNextMovie();
    } else {
        this->ui.UserListWidget->clear();
        this->ui.UserListWidget->addItem("No movies found for the given genre.");
    }
}

void GUI_USER::showNextMovie() {
    if (!iterationStopped && current_movie_index < filtered_movie_list.size()) {
        this->ui.UserListWidget->clear();
        const auto& movie = filtered_movie_list[current_movie_index];
        QString itemText = QString::fromStdString(movie.getTitle() + " - " + movie.getGenre() + " year: " + std::to_string(movie.getYear()) + " likes: " + std::to_string(movie.getLikes()) + " " + movie.getTrailer());
        this->ui.UserListWidget->addItem(itemText);
    } else if (iterationStopped && current_movie_index != -1) {
        this->ui.UserListWidget->clear();
        current_movie_index = -1;
        this->ui.UserListWidget->addItem("Iteration stopped by user.");
    }
}

void GUI_USER::onLikeButtonClicked() {
    if (current_movie_index < filtered_movie_list.size()) {
        try {
            user_list.Add_movie(filtered_movie_list[current_movie_index]);
        } catch (const std::runtime_error& e) {
        }
        current_movie_index = (current_movie_index + 1) % filtered_movie_list.size();
        showNextMovie();
    }
}

void GUI_USER::onNextButtonClicked() {
    if (current_movie_index < filtered_movie_list.size()) {
        current_movie_index = (current_movie_index + 1) % filtered_movie_list.size();
        showNextMovie();
    }
}

void GUI_USER::onDislikeButtonClicked() {
    iterationStopped = true;
    showNextMovie();
}

void GUI_USER::increaseLikeButtonHandler() {
    QString title = this->ui.TitleLineEdit->text();
    this->service.UpdateLikes(title.toStdString());
    this->user_list.Remove_movie(title.toStdString());
    this->displayUserWLButtonHandler();
}
