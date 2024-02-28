from src.domain.rental import *
import datetime
class RepositoryError(Exception):
    def __init__(self, error_message : str):
        self.__message = error_message

    @property
    def message(self):
        return self.__message

    def __str__(self):
        return self.__message

class RepoIterator:
    def __init__(self, data: list):
        self.__data = data
        self.__pos = -1

    def __next__(self):
        # return the next item we iterate over
        self.__pos += 1
        if self.__pos == len(self.__data):
            raise StopIteration()
        return self.__data[self.__pos]


class TextFileRepositoryRental:
    def __init__(self, file_name : str):
        self.__file_name = file_name
        self._data = {}
        self.__load_file()

    def __save_file(self):
        with open(self.__file_name, 'w') as file:
            for rental in self.get_data():
                file.write(str(rental.id) + "," + str(rental.book.id) + "," + str(rental.book.title) + "," + str(rental.book.author) + "," + str(rental.client.id) + "," + str(rental.client.name) + "," + str(rental.rented_date) + "," + str(rental.returned_date) + "\n")

        file.close()

    def __load_file(self):
        with open(self.__file_name, 'r') as file:
            for line in file.readlines():
                line = line.strip()
                elements_from_file = line.split(',')
                _id = int(elements_from_file[0])
                book_id = int(elements_from_file[1])
                book_title = elements_from_file[2]
                author = elements_from_file[3]
                client_id = int(elements_from_file[4])
                client_name = elements_from_file[5]

                rented_date_parts = elements_from_file[6].split('-')
                rented_date = date(int(rented_date_parts[0]), int(rented_date_parts[1]), int(rented_date_parts[2]))

                returned_date_parts = elements_from_file[7].split('-')
                returned_date = date(int(returned_date_parts[0]), int(returned_date_parts[1]), int(returned_date_parts[2]))
                self.add(Rental(_id, Book(book_id, book_title, author), Client(client_id, client_name), rented_date, returned_date))
        file.close()


    def add(self, object: id_object):

        if not isinstance(object, id_object):
            raise TypeError("Object must be an instance of id_object")

        if object in self._data.keys():
            raise RepositoryError("Object already exists")

        self._data[object.id] = object
        self.__save_file()

    def find(self, _id : int):
        if _id not in self._data:
            return None
        return self._data[_id]

    def remove(self, _id : int):
        if self.find(_id) == None:
            raise RepositoryError("Object does not exist")

        item = self.find(_id)
        self._data.pop(_id)
        self.__save_file()
        return item

    def __getitem__(self, item):
        if item not in self._data:
            raise RepositoryError("Object does not exist")
        return self._data[item]

    def __len__(self):
        return len(self._data)

    def __iter__(self):
        return RepoIterator(list(self._data.values()))

    def get_data(self):
        return list(self._data.values())

    def get_dict(self):
        return dict(self._data)


#if __name__ == '__main__':
    # book_repo = TextFileRepository("books_file")
    # for book in book_repo.get_data():
    #     print(book)
    # book = generate_random_book(20)
    # for item in book:
    #     book_repo.add(item)

    # file = open("books_file", "w")
    # with open("books_file", "w") as file:
    #     for book in book_repo.get_data():
    #         file.write(book.file_format())
    #         file.write("\n")
    # file.close()

    # with open("books_file", "r") as file:
    #     for line in range(0, 10)
    #
