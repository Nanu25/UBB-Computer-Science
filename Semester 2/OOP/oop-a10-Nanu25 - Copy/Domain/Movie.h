#pragma once

#include <string>
#include <istream>

class Movie {
private:
    std::string title, genre, trailer;
    int year_of_release;
    int number_of_likes;

public:

    Movie(const std::string title, const std::string genre, int year_of_release, int number_of_likes, const std::string trailer);
    Movie();

    std::string getTitle() const;
    std::string getGenre() const;
    std::string getTrailer() const;
    int getYear() const;
    int getLikes() const;
    void setLikes(int number_of_likes);
    std::string toString();

    // Insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << movie.title << "," << movie.genre << "," << movie.year_of_release << "," << movie.number_of_likes << ","<< movie.trailer;
        return os;
    }


    friend std::istream& operator>>(std::istream& is, Movie& movie) {
        std::getline(is >> std::ws, movie.title, ',');
        std::getline(is >> std::ws, movie.genre, ',');
        is >> movie.year_of_release;
        is.ignore(); // ignore the comma
        is >> movie.number_of_likes;
        is.ignore();
        std::getline(is >> std::ws, movie.trailer);
        return is;
    }
};
