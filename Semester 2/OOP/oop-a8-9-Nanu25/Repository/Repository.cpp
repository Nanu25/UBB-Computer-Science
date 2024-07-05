#include <stdexcept>
#include <algorithm>
#include "Repository.h"

void Repository::Add(Movie x) {
    auto it = std::find_if(this->repo.begin(), this->repo.end(), [&x](const Movie& movie) {
        return movie.getTitle() == x.getTitle();
    });

    if(it != repo.end())
        throw std::runtime_error("This film already exists.");

    this->repo.push_back(x);
}


void Repository::Delete(std::string title) {
    auto it = std::find_if(repo.begin(), repo.end(), [&title](const Movie& movie) {
        return movie.getTitle() == title;
    });

    if (it == repo.end()) {
        throw std::runtime_error("This movie doesn't exist");
    }

    repo.erase(it);
}

Movie Repository::getElement(int position) {
    return this->repo[position];
}

int Repository::getRepoLength() {
    return this->repo.size();
}

void Repository::Update(std::string title, Movie x) {
    auto it = std::find_if(repo.begin(), repo.end(), [&title](const Movie& movie) {
        return movie.getTitle() == title;
    });

    if (it == repo.end()) {
        throw std::runtime_error("This movie doesn't exist");
    }

    *it = x; // Update the movie at the found position
}

void Repository::setElem(int position, Movie x) {
    if(position < 0 && position > this->repo.size())
            throw std::runtime_error("Index out of range");
    this->repo[position] = x;
}

std::vector<TElement>& Repository::getRepo() {
    return this->repo;
}

void Repository::save_data_to_file() {
//    std::ofstream fout("../repo.csv");
//    if (!fout.is_open()) {
//        std::cerr << "Error opening file: " << "../repo.csv" << std::endl;
//        return;
//    }
//
//    for (const auto& movie : this->repo) {
//        fout << movie << std::endl;
//    }
//
//    fout.close();
}

void Repository::readMoviesFromFile(std::string filename){
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open the file.\n";
        return;
    }

    Movie movie;
    while (file >> movie) {
        this->repo.push_back(movie);
    }

    file.close();
}

