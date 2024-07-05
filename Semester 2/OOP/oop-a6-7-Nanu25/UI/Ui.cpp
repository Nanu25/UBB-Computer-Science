#include "Ui.h"
#include "../Validator.h"
#include <iostream>
#include <algorithm>
#include <fstream>

const int ADMINISTRATOR_MODE = 1;
const int ADD_MOVIE = 1;
const int REMOVE_MOVIE = 2;
const int UPDATE_MOVIE = 3;
const int PRINT_LIST =4;
const int DISPLAY_ALL_MOVIES_GIVEN_GENRE = 1;
const int DELETE_MOVIE_WATCH_LIST = 2;
const int DISPLAY_WATCH_LIST = 4;
const int STOP = 2;
const int PRINT_WATCH_LIST = 3;

Ui::Ui(Service serv_list, Service user_list): service_list(serv_list), user_list(user_list) {}

void Init_list(Service movie_list) {
//    movie_list.Add_movie(Movie{"The Shawshank Redemption", "Drama", 1994, 2000, "https://www.youtube.com/watch?v=6hB3S9bIaco"});
//    movie_list.Add_movie(Movie{"The Godfather", "Crime", 1972, 1800, "https://www.youtube.com/watch?v=sY1S34973zA"});
//    movie_list.Add_movie(Movie{"The Dark Knight", "Action", 2008, 1900, "https://www.youtube.com/watch?v=EXeTwQWrcwY"});
//    movie_list.Add_movie(Movie{"Schindler's List", "Biography", 1993, 1700, "https://www.youtube.com/watch?v=JdRGC-w9syA"});
//    movie_list.Add_movie(Movie{"Pulp Fiction", "Crime", 1994, 1800, "https://www.youtube.com/watch?v=s7EdQ4FqbhY"});
//    movie_list.Add_movie(Movie{"The Lord of the Rings: The Return of the King", "Fantasy", 2003, 2200, "https://www.youtube.com/watch?v=r5X-hFf6Bwo"});
//    movie_list.Add_movie(Movie{"Forrest Gump", "Drama", 1994, 2000, "https://www.youtube.com/watch?v=bLvqoHBptjg"});
//    movie_list.Add_movie(Movie{"Inception", "Science Fiction", 2010, 2100, "https://www.youtube.com/watch?v=YoHD9XEInc0"});
//    movie_list.Add_movie(Movie{"The Matrix", "Science Fiction", 1999, 1850, "https://www.youtube.com/watch?v=m8e-FF8MsqU"});
//    movie_list.Add_movie(Movie{"Fight Club", "Drama", 1999, 1600, "https://www.youtube.com/watch?v=SUXWAEX2jlg"});

//    Movie movie;
//    std::ifstream f("../repo_data");
//    while(f >> movie) {
//        movie_list.Add_movie(movie);
//    }
}

void print_menu() {
    std::cout << "1 for administrator mode\n";
    std::cout << "2 for user mode \n";
}

void print_administrator_option() {
    std::cout << "1 for add a new movie\n";
    std::cout << "2 for remove an existing movie\n";
    std::cout << "3 for update a movie\n";
    std::cout << "4 to print the list of movies\n";
    std::cout << "0 to exit\n";

}

void print_user_option() {
    std::cout << "1 to see all the movies having a given genre in the database\n";
    std::cout << "2 for delete a movie from the watchlist\n";
    std::cout << "3 for print the watchlist\n";
    std::cout << "4 for display the watchlist\n";
    std::cout << "0 to exit\n";
}

void print_movie_list(Service movie_list) {
    std::for_each(movie_list.get_list().getRepo().begin(), movie_list.get_list().getRepo().end(), [](const TElement& movie) {
        std::cout << "Movie title: " << movie.getTitle() << '\n';
        std::cout << "Movie genre: " << movie.getGenre() << '\n';
        std::cout << "Movie year of release: " << movie.getYear() << '\n';
        std::cout << "Number of likes: " << movie.getLikes() << '\n';
        std::cout << "Trailer link: " << movie.getTrailer() << '\n';
        std::cout << '\n';
    });
}

void Ui::ValidateMovie(Movie movie)  {
    try {
        MovieValidator::validate(movie);
        this->service_list.Add_movie(movie);
    }
    catch (ValidatorException& ex) {
        std::cout << ex.getMessage();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error occurred: " << e.what() << '\n';
    }
}



void Ui::start() {
    print_menu();

    int mode;
    std::cout << ">";
    std::cin >> mode;
    while(true) {
        if(mode == ADMINISTRATOR_MODE) {
            print_administrator_option();
            int option;
            std::cout << ">";
            std::cin >> option;

            if(option == ADD_MOVIE) {
                std::cin.get();
                std::cout << "Tell the movie title:\n";
                std::string title;
                std::getline(std::cin, title);

                std::cout << "Tell the genre of the movie:\n";
                std::string genre;
                std::cin >> genre;

                std::cout << "Tell the year of release:\n";
                int year;
                std::cin >> year;

                std::cout << "Tell the numbers of likes:\n";
                int likes;
                std::cin >> likes;

                std::cout << "Insert the link of the trailer:\n";
                std::string trailer;
                std::cin >> trailer;

                Movie m{title, genre, year, likes, trailer};
                //ValidateMovie(m);
  //              try {
                    ValidateMovie(m);

                    //this->service_list.Add_movie(Movie{title, genre, year, likes, trailer});
//                }
//                catch (const std::runtime_error& e) {
//                    std::cerr << "Error occurred: " << e.what() << '\n';
//                }
            }else if(option == REMOVE_MOVIE) {
                std::cin.get();
                std::cout << "Tell the movie title you want to delete:\n";
                std::string title;
                std::getline(std::cin, title);

                try {
                    this->service_list.Remove_movie(title);
                }
                catch (const std::runtime_error& e) {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }

            }else if(option == UPDATE_MOVIE) {
                std::cin.get();
                std::cout << "Tell the movie title you want to update.:\n";
                std::string title;
                std::getline(std::cin, title);

                std::cout << "Tell the movie title:\n";
                std::string new_title;
                std::getline(std::cin, new_title);

                std::cout << "Tell the genre of the movie:\n";
                std::string genre;
                std::cin >> genre;

                std::cout << "Tell the year of release:\n";
                int year;
                std::cin >> year;

                std::cout << "Tell the numbers of likes:\n";
                int likes;
                std::cin >> likes;

                std::cout << "Insert the link of the trailer:\n";
                std::string trailer;
                std::cin >> trailer;

                try {
                    this->service_list.Update_movie(title, Movie{new_title, genre, year, likes, trailer});
                }
                catch (const std::runtime_error& e) {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }

            }else if(option == PRINT_LIST) {
                //print_movie_list(this->service_list);
                this->service_list.save_repo_file();
            }else {
                this->service_list.save_repo_file();
                break;
            }
        }else {
            print_user_option();
            int option;
            std::cout << ">";
            std::cin >> option;
            std::cin.get();
            if(option == DISPLAY_ALL_MOVIES_GIVEN_GENRE) {
                std::string genre;
                std::cout << "Give the genre of the movies\n";
                std::getline(std::cin, genre);
                std::vector <TElement> filtered_movie_list = this->service_list.get_movies_given_genre(genre);

                int i = 0;
                while(i < filtered_movie_list.size()) {
                    std::cout << "Movie title: " << filtered_movie_list[i].getTitle() << '\n';
                    std::cout << "Movie genre: " << filtered_movie_list[i].getGenre() << '\n';
                    std::cout << "Movie year of release: " << filtered_movie_list[i].getYear() << '\n';
                    std::cout << "Number of likes: " << filtered_movie_list[i].getLikes() << '\n';
                    std::cout << "Trailer link: " << filtered_movie_list[i].getTrailer() << '\n';
                    std::cout << '\n';

                    std::cout << "Do you like the movie?\n";
                    std::cout << "1 for yes\n";
                    std::cout << "2 for no\n";

                    int like;
                    std::cin >> like;
                    if(like == 1) {
                        try {
                            user_list.Add_movie(filtered_movie_list[i]);
                        }catch (const std::runtime_error& e) {
                            std::cerr << "Error occurred: " << e.what() << '\n';
                        }
                    }
                    std::cout << "Do you want to continue?\n";
                    std::cout << "1 for yes\n";
                    std::cout << "2 for no\n";
                    int answer;
                    std::cin >> answer;

                    if(answer == STOP)
                        break;

                    i = (i + 1) % filtered_movie_list.size();
                }
            }else if(option == DELETE_MOVIE_WATCH_LIST) {
                std::string title;
                std::cout << "Tell the movie title you want to remove\n";
                std::getline(std::cin, title);

                try {
                    user_list.Remove_movie(title);

                    std::cout << "Do you like the movie?\n";
                    std::cout << "1 for yes\n";
                    std::cout << "2 for no\n";
                    int answer;
                    std::cin >> answer;
                    if (answer == 1)
                        this->service_list.UpdateLikes(title);
                }catch (const std::runtime_error& e) {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }

            }else if(option == PRINT_WATCH_LIST) {
                print_movie_list(user_list);
            }else if(option == DISPLAY_WATCH_LIST) {
                this->user_list.save_repo_file();
            }else {
                this->user_list.save_repo_file();
                break;
            }
        }
    }
    //this->user_list.save_repo_file("");
}

