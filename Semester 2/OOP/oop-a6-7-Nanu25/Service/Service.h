#pragma once

#include "../Repository/Repository.h"

class Service {
private:
    Repository& service_list;
public:
    Service(Repository& movie_list);
    void Add_movie(Movie x);
    void Remove_movie(std::string title);
    void Update_movie(std::string title, Movie x);
    void UpdateLikes(std::string title);
    Repository& get_list();
    std::vector <TElement> get_movies_given_genre(std::string user_genre);
    void save_repo_file();
    void load_repo_file(std::string filename);
};


