#pragma once

#include "Repository.h"

class FileRepository: public Repository{
protected:
    std::string filename;

    void readMoviesFromFile(std::string filename);
    void save_data_to_file();
public:
    FileRepository(std::string filename);
    void Add(Movie x) override;
    void Delete(std::string title) override;
    void Update(std::string title, Movie x) override;
    std::string getFilename();
    //virtual std::vector<TElement> &getRepo() const = 0;
};


