
#include "Movie.h"

Movie::Movie(const std::string title, const std::string genre, int year_of_release, int number_of_likes, const std::string trailer) {
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->trailer = trailer;
}

Movie::Movie() {
    this->title = "";
    this->genre = "";
    this->year_of_release = 0;
    this->number_of_likes = 0;
    this->trailer = "";

}

std::string Movie::getTitle() const {
    return this->title;
}

std::string Movie::getGenre() const {
    return this->genre;
}

int Movie::getYear() const {
    return this->year_of_release;
}

int Movie::getLikes() const {
    return this->number_of_likes;
}

std::string Movie::getTrailer() const {
    return this->trailer;
}

void Movie::setLikes(int number_of_likes) {
    this->number_of_likes = number_of_likes;
}


