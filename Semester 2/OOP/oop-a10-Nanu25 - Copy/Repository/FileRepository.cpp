#include "FileRepository.h"

FileRepository::FileRepository(std::string filename) {
    this->filename = filename;
}


//void FileRepository::save_data_to_file() {
//    std::ofstream fout(this->filename);
//    if (!fout.is_open()) {
//        std::cerr << "Error opening file: " << this->filename << std::endl;
//        return;
//    }
//
//    for (const auto& movie : this->getRepo()) {
//        fout << movie << std::endl;
//    }
//
//    fout.close();
//}
//
//void FileRepository::readMoviesFromFile() {
//    std::ifstream file(this->filename);
//    if (!file) {
//        std::cerr << "Error: Could not open the file.\n";
//        return;
//    }
//
//    Movie movie;
//    while (file >> movie) {
//        Repository::Add(movie);
//    }
//
//    file.close();
//}

void FileRepository::Add(Movie x) {
    Repository::Add(x);
    this->save_data_to_file();
}

void FileRepository::Delete(std::string title) {
    Repository::Delete(title);
    this->save_data_to_file();
}


void FileRepository::Update(std::string title, Movie x) {
    Repository::Update(title, x);
    this->save_data_to_file();
}

void FileRepository::readMoviesFromFile(std::string filename) {
    Repository::readMoviesFromFile(filename);
}

void FileRepository::save_data_to_file() {
    std::ofstream fout(this->filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file: " << this->filename << std::endl;
        return;
    }

    for (const auto& movie : this->getRepo()) {
        fout << movie << std::endl;
    }

    fout.close();
}

std::string FileRepository::getFilename() {
    return this->filename;
}

//std::vector<TElement> &FileRepository::getRepo() {
//    return Repository::getRepo();
//}



