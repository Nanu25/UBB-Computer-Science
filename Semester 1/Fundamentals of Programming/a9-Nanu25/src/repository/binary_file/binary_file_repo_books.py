import pickle

from src.domain.Id_object import id_object
from src.domain.book import generate_random_book
from src.repository.memory_repository import MemoryRepository


#from src.repository.text_file.text_file_repo_books import TextFileRepositoryBook


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


class BinaryFileRepoBooks:
    def __init__(self, file_name : str):
        self.__file_name = file_name
        self._data = {}
        self.__load_file()

    def __load_file(self):
        try:
            file = open(self.__file_name, "rb")
            self._data = pickle.load(file)
            file.close()
        except FileNotFoundError:
            print("Not found")
        except OSError:
            raise RepositoryError("Cannot start the repository")

    def __save_file(self):
        file = open(self.__file_name, "wb")
        pickle.dump(self._data, file)
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
    #Asa scriem intr un binary. Sa am grija sa scriu un dict!!!
    # books = generate_random_book(20)
    # repo_books = MemoryRepository()
    # for book in books:
    #     repo_books.add(book)
    #
    #
    #
    # with open("books_binary", "wb") as binary_file:
    #     pickle.dump(repo_books.get_dict(), binary_file)

    # repo_binary_book = BinaryFileRepoBooks("books_binary")
    # for book in repo_binary_book:
    #     print(book)

