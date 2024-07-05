#include "HTMLRepository.h"

HTMLRepository::HTMLRepository(std::string name) {
    this->filename = name;
}

void HTMLRepository::readMoviesFromFile(std::string filename) {
    Repository::readMoviesFromFile(filename);
}

std::string generateHTML(std::vector<Movie> movies) {
    std::string htmlContent = "<!DOCTYPE html>\n"
                              "<html>\n"
                              "<head>\n"
                              "    <title>Movie Playlist</title>\n"
                              "</head>\n"
                              "<body>\n"
                              "<table border=\"1\">\n"
                              "    <tr>\n"
                              "        <td>Title</td>\n"
                              "        <td>Genre</td>\n"
                              "        <td>Year of Release</td>\n"
                              "        <td>Likes</td>\n"
                              "        <td>Trailer</td>\n"
                              "    </tr>\n";

    for (const auto& movie : movies) {
        htmlContent += "    <tr>\n";
        htmlContent += "        <td>" + movie.getTitle() + "</td>\n";
        htmlContent += "        <td>" + movie.getGenre() + "</td>\n";
        htmlContent += "        <td>" + std::to_string(movie.getYear()) + "</td>\n";
        htmlContent += "        <td>" + std::to_string(movie.getLikes()) + "</td>\n";
        htmlContent += "        <td><a href=\"" + movie.getTrailer() + "\">Trailer</a></td>\n";
        htmlContent += "    </tr>\n";
    }

    htmlContent += "</table>\n"
                   "</body>\n"
                   "</html>";

    return htmlContent;
}

void HTMLRepository::save_data_to_file() {
    std::ofstream fout("../watchList.html");
    fout << generateHTML(this->getRepo());
    fout.close();
    system("H:\\OOP\\Labs\\oop-a6-7-Nanu25\\watchList.html");
}
