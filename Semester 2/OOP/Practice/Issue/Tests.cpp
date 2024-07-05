//
// Created by alex_ on 6/23/2024.
//

#include <cassert>
#include "Tests.h"
#include "Repository.h"
#include "Service.h"

void Tests::testAll() {
    Repository repo{};
    repo.AddIssue(Issue{"dasdsa", "open", "dsa", "dsa"});
    assert(repo.getIssueRepo().size() == 1);

    Service serv{repo};
    serv.ResolveIssue(0, "Alex");
    assert(serv.getRepository().getIssueRepo()[0].getSolver() == "Alex");
}
