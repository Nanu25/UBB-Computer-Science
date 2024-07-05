#include "Validator.h"

ValidatorException::ValidatorException(std::string message) {
    this->message = message;
}

std::string ValidatorException::getMessage() {
    return this->message;
}

void MovieValidator::validate(Movie &movie) {
    std::string errors = "";
    if(movie.getYear() > 2024)
        errors += "This year is too far!\n";
    if(movie.getLikes() < 0)
        errors += "A movie cannot have negative likes\n";
    if(movie.getTitle().empty())
        errors += "Movie title cannot be empty\n";


    if(movie.getGenre().size() < 2)
        errors += "Movie genre cannot be less than 3\n";


    if(movie.getTrailer().empty())
        errors += "Movie trailer link cannot be empty\n";

    if(movie.getTrailer().substr(0, 5) != "https")
        errors += "Movie trailer link must start with 'https'\n";


    if(errors.size() > 0)
        throw ValidatorException(errors);
}
