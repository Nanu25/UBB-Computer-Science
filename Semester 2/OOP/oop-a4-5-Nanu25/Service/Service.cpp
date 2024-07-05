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

DynamicArray<TElement> Service::get_movies_given_genre(std::string user_genre) {
    DynamicArray<TElement> movie_list;
    for(int i = 0; i < this->service_list.getRepoLength(); i++)
        if(user_genre == this->service_list.getElement(i).getGenre() || user_genre == "") {
            movie_list.add(this->service_list.getElement(i));
        }

    return movie_list;
}

//
void Service::UpdateLikes(std::string title) {
    int poz = this->service_list.Find(title);
    int last_like = this->service_list.getElement(poz).getLikes();
    Movie x = this->service_list.getElement(poz);       //the initial movie.
    x.setLikes(last_like + 1);                    //add one like more.
    this->service_list.Delete(title);                           //delete the old version
    this->Add_movie(x);                                         //add the new version.
}


