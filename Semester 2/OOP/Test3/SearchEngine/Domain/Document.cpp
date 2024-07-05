
#include "Document.h"

Document::Document() {

}

Document::Document(std::string name, std::string keyword, std::string content) {
    this->name = name;
    this->keyword = keyword;
    this->content = content;
}

std::string Document::getName() {
    return this->name;
}

std::string Document::getKeyword() {
    return this->keyword;
}

std::string Document::toStr() {
    return this->name + " " +  this->keyword;

}
