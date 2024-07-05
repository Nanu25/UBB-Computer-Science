
#ifndef TESTPROFA_SERVICE_H
#define TESTPROFA_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service : public Subject {
private:
    Repository& repo_list;
public:
    Service(Repository& repo);

    void AddDeveloper(Development devo);
    void AddIssue(Issue issue);

    void RemoveIssue(std::string desc);
    void ResolveIssue(int index, std::string name);
    Repository& getRepository();
    std::vector<Issue> sortIssue();
};


#endif //TESTPROFA_SERVICE_H
