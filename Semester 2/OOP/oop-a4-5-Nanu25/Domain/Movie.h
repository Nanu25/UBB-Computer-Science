#pragma once

#include <string>

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
};
