//
// Created by alex_ on 6/22/2024.
//

#include <algorithm>
#include <iostream>
#include "Service.h"

Service::Service(Repository &repo) : repo_list{repo}{

}

void Service::AddDeveloper(Development devo) {
    this->repo_list.AddDevelopment(devo);
}

void Service::AddIssue(Issue issue) {
    this->repo_list.AddIssue(issue);
    this->notify();
}

Repository &Service::getRepository() {
    return this->repo_list;
}

//bool cmp(Issue i1, Issue i2) {
  //  return i1.getStatus()  < i2.getStatus() || (i1.getStatus() == i2.getStatus() && i1.getDescription() < i2.getDescription());
//}

std::vector<Issue> Service::sortIssue() {
  //  std::vector <Issue> aux = this->repo_list.getIssueRepo();
    //std::sort(aux.begin(), aux.end(), cmp);
    return this->repo_list.getIssueRepo();
}

void Service::RemoveIssue(std::string desc) {
    this->repo_list.removeIssue(desc);
    this->notify();
}

void Service::ResolveIssue(int index, std::string name) {
    if(this->repo_list.getIssueRepo()[index].getStatus() == "closed")
        throw std::runtime_error("This issue is already solved");
    this->repo_list.getIssueRepo()[index].setSolver(name);
    this->repo_list.getIssueRepo()[index].setStatus("closed");

    this->notify();
}
