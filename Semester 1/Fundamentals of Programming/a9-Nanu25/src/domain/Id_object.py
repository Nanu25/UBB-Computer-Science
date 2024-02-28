
class id_object:
    def __init__(self, _id : int):
        if not isinstance(_id, int):
            raise TypeError("id must be an integer")
        self.__id = _id

    @property
    def id(self):
        return self.__id

