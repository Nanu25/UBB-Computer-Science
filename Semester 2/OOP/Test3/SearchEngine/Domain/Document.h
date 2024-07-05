
#ifndef SEARCHENGINE_DOCUMENT_H
#define SEARCHENGINE_DOCUMENT_H


#include <string>

class Document {
private:
    std::string name, keyword, content;
public:
    Document();
    Document(std::string  name, std::string keyword, std::string content);
    std::string getName();
    std::string getKeyword();

    std::string toStr();

};


#endif //SEARCHENGINE_DOCUMENT_H
