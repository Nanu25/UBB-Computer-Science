
#include <fstream>
#include "Repository.h"

std::vector<Document> Repository::getRepo() {
    return this->repo;
}

void Repository::load_file(std::string filename) {
    std::ifstream f(filename);
    std::string s;
    while(std::getline(f, s)) {
        std::string name;
        int i = 0;
        while(s[i] != '|')
            name += s[i++];
        i++;
        name.pop_back();

        std::string keyword;
        while(s[i] != '|')
            keyword += s[i++];
        i++;
        keyword.pop_back();

        std::string content;
        while(i < s.size())
            content += s[i++];

        repo.push_back(Document(name, keyword, content));

    }
}
