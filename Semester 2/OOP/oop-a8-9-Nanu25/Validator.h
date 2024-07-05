#pragma once

#include <exception>
#include <string>
#include "Domain/Movie.h"

class ValidatorException  {
private:
    std::string message;
public:
    ValidatorException(std::string message);
    std::string getMessage();
};

class MovieValidator {
public:
    static void validate(Movie &movie);
};


