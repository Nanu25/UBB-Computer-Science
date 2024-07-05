
#ifndef TESTPROFA_REPOSITORY_H
#define TESTPROFA_REPOSITORY_H


#include <vector>
#include "Development.h"
#include "Issue.h"
#include "Observer.h"

class Repository {
private:
    std::vector <Development> devo_repo;
    std::vector <Issue> issue_repo;
    std::string filename;
public:
    Repository();

    void AddDevelopment(Development dev);
    void AddIssue(Issue issue);
    void removeIssue(std::string desc);

    std::vector<Development> getDevoRepo();
    std::vector <Issue>& getIssueRepo();

    void readFile();
    void writeFile();


};


#endif //TESTPROFA_REPOSITORY_H
