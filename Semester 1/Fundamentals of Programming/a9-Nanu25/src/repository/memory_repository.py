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
        self._data = {}

    def add(self, object: id_object):

        if not isinstance(object, id_object):
            raise TypeError("Object must be an instance of id_object")

        if object in self._data.keys():
            raise RepositoryError("Object already exists")

        self._data[object.id] = object


    def find(self, _id : int):
        if _id not in self._data:
            return None
        return self._data[_id]

    def remove(self, _id : int):
        if self.find(_id) == None:
            raise RepositoryError("Object does not exist")

        item = self.find(_id)
        self._data.pop(_id)
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
