
#include <cassert>
#include <stdexcept>
#include "tests.h"


void tests::testsDynamicArray() {
    DynamicArray <TElement> da{ 2 };

    assert(da.getCapacity() == 2);
    assert(da.getLength() == 0);

    Movie p{ "Venom", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    da.add(p);
    assert(da.getLength() == 1);

    Movie p2{ "Stan si bran", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    da.add(p2);
    assert(da.getLength() == 2);

    // capacity must double
    Movie p3{ "Denis pericol public", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    da.add(p3);
    assert(da.getLength() == 3);
    assert(da.getCapacity() == 4);

    da.remove(0);
    assert(da.getLength() == 2);

    da.update(0, p3);
    assert(da.getElem(0).getTitle() == "Denis pericol public");

    try {
        da.remove(5);
    }
    catch (std::out_of_range&) {
        assert(true);
    }

    try {
        da.getElem(5);
    }
    catch (std::out_of_range&) {
        assert(true);
    }

    try {
        da.setElement(5, p3);
    }
    catch (std::out_of_range&) {
        assert(true);
    }

    Movie x  = da.getElem(0);
    x.setLikes(2000);
    assert(x.getLikes() == 2000);
}

void tests::testRepo() {
    Repository repo;
    Movie p3{ "Denis pericol public", "Comedy", 2019, 1000, "https://www.youtube.com/watch?v=u9Mv98Gr5pY" };
    repo.Add(p3);

    assert(repo.getRepoLength() == 1);
    assert(repo.Find("Denis pericol public") != -1);

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

    DynamicArray <TElement> result = service.get_movies_given_genre("Comedy");
    assert(result.getLength() == 1);
    assert(result.getElem(0).getTitle() == "Denis pericol public");

    service.UpdateLikes("Denis pericol public");
}


void tests::testAll() {
    testsDynamicArray();
    testRepo();
    testService();
}
