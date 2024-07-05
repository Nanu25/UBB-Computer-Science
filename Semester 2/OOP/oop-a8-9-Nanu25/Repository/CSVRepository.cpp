#include <fstream>
#include "CSVRepository.h"
#include <iostream>

void CSVRepository::readMoviesFromFile(std::string filename) {
    Repository::readMoviesFromFile(filename);
}

void CSVRepository::save_data_to_file() {
    std::ofstream fout(this->filename);
    if (!fout.is_open()) {
        std::cerr << "Error opening file: " << this->filename << std::endl;
        return;
    }

    for (const auto& movie : this->getRepo()) {
        fout << movie << std::endl;
    }

    fout.close();
    std::system(("start excel " + std::string(this->filename)).c_str());
}

