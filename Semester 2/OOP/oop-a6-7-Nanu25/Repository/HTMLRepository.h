#pragma once

#include "Repository.h"

class HTMLRepository : public Repository{
private:
    std::string filename;
public:
    HTMLRepository(std::string name);
    void readMoviesFromFile(std::string filename) override;
    void save_data_to_file() override;
};


