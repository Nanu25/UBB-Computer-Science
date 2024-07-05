#include "GUI.h"
#include "../Validator.h"
#include <qlayout.h>
#include <qlabel.h>


GUI::GUI(Service& serv) : serv{ serv }
{
    this->buildGUI();
    //this->populateList();

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);
    QObject::connect(this->printButton, &QPushButton::clicked, this, &GUI::printButtonHandler);
}


void GUI::buildGUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout{ this };
    this->moviesListWidget = new QListWidget{};
    mainLayout->addWidget(moviesListWidget);

    QGridLayout* rightLayout = new QGridLayout{};

    QLabel* titleLabel = new QLabel{ "Title" };
    this->title = new QLineEdit{};
    QLabel* genreLabel = new QLabel{ "Genre" };
    this->genre = new QLineEdit{};
    QLabel* yearLabel = new QLabel{ "Year" };
    this->year = new QLineEdit{};
    QLabel* likesLabel = new QLabel{ "Likes" };
    this->likes = new QLineEdit{};
    QLabel* trailerLabel = new QLabel{ "Trailer" };
    this->trailer = new QLineEdit{};

    rightLayout->addWidget(titleLabel, 0, 0);
    rightLayout->addWidget(this->title, 0, 1);
    rightLayout->addWidget(genreLabel, 1, 0);
    rightLayout->addWidget(this->genre, 1, 1);
    rightLayout->addWidget(yearLabel, 2, 0);
    rightLayout->addWidget(this->year, 2, 1);
    rightLayout->addWidget(likesLabel, 3, 0);
    rightLayout->addWidget(this->likes, 3, 1);
    rightLayout->addWidget(trailerLabel, 4, 0);
    rightLayout->addWidget(this->trailer, 4, 1);

    this->addButton = new QPushButton{ "Add" };
    this->deleteButton = new QPushButton{ "Delete" };
    this->updateButton = new QPushButton{ "Update" };
    this->printButton = new QPushButton{"Display"};

    rightLayout->addWidget(this->addButton, 5, 0);
    rightLayout->addWidget(this->deleteButton, 5, 1);
    rightLayout->addWidget(this->updateButton, 6, 0);
    rightLayout->addWidget(this->printButton, 6, 1);

    mainLayout->addLayout(rightLayout);
}

void GUI::populateList()
{
    this->moviesListWidget->clear();

    Repository repo = this->serv.get_list();
    for (auto s : repo.getRepo())
    {
        //this->spaceshipListWidget->addItem(QString::fromStdString(s.getTitle()));
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.getTitle() + " " + s.getGenre() + " " + std::to_string(s.getYear()) + " " + std::to_string(s.getLikes()) + " " + s.getTrailer()) };
        QFont font{ "Arial", 12};
        item->setFont(font);
        this->moviesListWidget->addItem(item);

    }
}

void GUI::addButtonHandler()
{
    QString title = this->title->text();
    QString genre = this->genre->text();
    int year = this->year->text().toInt();
    int likes = this->likes->text().toInt();
    QString trailer = this->trailer->text();

    Movie newMovie{ title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString() };

    try {
        MovieValidator::validate(newMovie);
        this->serv.Add_movie(newMovie); // Add the movie only if it passes validation
        this->populateList();
        this->serv.save_repo_file();

    }
    catch (ValidatorException& e) {

    }
}

void GUI::deleteButtonHandler()
{
    QString title = this->title->text();
    try {
        this->serv.Remove_movie(title.toStdString());
        this->populateList();
        //this->serv.save_repo_file();

    }
    catch (const std::runtime_error& e) {

    }
}

void GUI::updateButtonHandler()
{
    QString title = this->title->text();
    QString genre = this->genre->text();
    int year = this->year->text().toInt();
    int likes = this->likes->text().toInt();
    QString trailer = this->trailer->text();

    try {
        this->serv.Update_movie(title.toStdString(), Movie{title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString()});
        this->populateList();
    }
    catch (const std::runtime_error& e) {

    }
    //this->serv.save_repo_file();
}

void GUI::printButtonHandler() {
    this->populateList();
}
