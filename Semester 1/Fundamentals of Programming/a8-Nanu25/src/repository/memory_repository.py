from src.domain.Id_object import id_object


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


class MemoryRepository:
    def __init__(self):
        self.__data = {}

    def add(self, object: id_object):

        if not isinstance(object, id_object):
            raise TypeError("Object must be an instance of id_object")

        if object in self.__data.keys():
            raise RepositoryError("Object already exists")

        self.__data[object.id] = object


    def find(self, _id : int):
        if _id not in self.__data:
            return None
        return self.__data[_id]

    def remove(self, _id : int):
        if self.find(_id) == None:
            raise RepositoryError("Object does not exist")

        return self.__data.pop(_id)

    def __getitem__(self, item):
        if item not in self.__data:
            raise RepositoryError("Object does not exist")
        return self.__data[item]

    def __len__(self):
        return len(self.__data)

    def __iter__(self):
        return RepoIterator(list(self.__data.values()))

    def get_data(self):
        return list(self.__data.values())
