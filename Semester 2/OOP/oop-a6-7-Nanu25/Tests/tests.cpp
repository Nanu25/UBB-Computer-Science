
#include <cassert>
#include <stdexcept>
#include "tests.h"

void tests::testRepo() {
    Repository repo;
    Movie p3{ "Denis pericol public", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    repo.Add(p3);

    assert(repo.getRepoLength() == 1);

    repo.Update("Denis pericol public", Movie{ "Aaa", "comedy", 2020, 1000, "asdasd" });
    assert(repo.getElement(0).getTitle() == "Aaa");

    Movie p{ "Venom", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    repo.setElem(0, p);
    assert(repo.getElement(0).getTitle() == "Venom");

    repo.Delete("Venom");
    assert(repo.getRepoLength() == 0);

    try {
        repo.Delete("Venom");
    }
    catch (std::runtime_error&) {
        assert(true);
    }

    try {
        repo.Update("Venom", Movie{ "Aaa", "comedy", 2020, 1000, "asdasd" });
    }
    catch (std::runtime_error&) {
        assert(true);
    }

    repo.Add(p);


    try {
        repo.Add(p);
    }
    catch (std::runtime_error&) {
        assert(true);
    }
}


void tests::testService() {
    Repository repo;
    Movie p3{ "Denis pericol public", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    repo.Add(p3);
    Movie p{ "Venom", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    repo.Add(p);

    Service service{ repo };
    service.Add_movie(Movie{ "Aaa", "comedy", 2020, 1000, "asdasd" });
    assert(service.get_list().getRepoLength() == 3);

    service.Remove_movie("Aaa");
    assert(service.get_list().getRepoLength() == 2);

    service.Update_movie("Venom", Movie{ "Forrest Gump", "Drama", 1994, 2000, "https://www.youtube.com/watch?v=bLvqoHBptjg" });
    assert(service.get_list().getElement(1).getTitle() == "Forrest Gump");
    assert(service.get_list().getElement(1).getGenre() == "Drama");
    assert(service.get_list().getElement(1).getYear() == 1994);
    assert(service.get_list().getElement(1).getLikes() == 2000);
    assert(service.get_list().getElement(1).getTrailer() == "https://www.youtube.com/watch?v=bLvqoHBptjg");

    std::vector<TElement> result = service.get_movies_given_genre("Comedy");
    assert(result.size() == 1);
    assert(result[0].getTitle() == "Denis pericol public");

    service.UpdateLikes("Denis pericol public");
}


void tests::testAll() {
    testRepo();
    testService();
}
