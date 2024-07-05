#include <algorithm>
#include "Service.h"

Service::Service(Repository& movie_list) : service_list{movie_list} {}

void Service::Add_movie(Movie x) {
    this->service_list.Add(x);
}

Repository& Service::get_list() {
    return this->service_list;
}

void Service::Remove_movie(std::string title) {
    this->service_list.Delete(title);
}

void Service::Update_movie(std::string title, Movie x) {
    this->service_list.Update(title, x);
}

std::vector<TElement> Service::get_movies_given_genre(std::string user_genre) {
    std::vector<TElement> movie_list;

    //We need to make a copy for repository
    std::vector<TElement> repo = this->service_list.getRepo();

    std::copy_if(repo.begin(), repo.end(), std::back_inserter(movie_list),
                 [&](const TElement& elem) {
                     return user_genre == elem.getGenre() || user_genre == "";
                 });
    return movie_list;
}

void Service::UpdateLikes(std::string title) {
    auto& repo = this->service_list.getRepo();
    std::for_each(repo.begin(), repo.end(), [&](TElement& elem) {
             if (elem.getTitle() == title) {
                 int last_like = elem.getLikes();
                 elem.setLikes(last_like + 1);
             }
         });
}

void Service::save_repo_file(){
    this->service_list.save_data_to_file();
}

void Service::load_repo_file(std::string filename) {
    this->service_list.readMoviesFromFile(filename);
}


