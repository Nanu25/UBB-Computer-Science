import random
from src.domain.Id_object import id_object
from src.utilities.const import *

class Client(id_object):
    def __init__(self, _id,  name : str):
        super().__init__(_id)
        if not isinstance(name, str):
            raise TypeError('Name must be a string')
        self.__name = name

    def __str__(self):
        return f'Id: {self.id}  Name: {self.name}'

    @property
    def name(self):
        return self.__name


def generate_random_clients(number_to_generate = NUMBER_TO_GENERATE) -> list:
    given_names = ["Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Henry", "Ivy", "Jack", "Kelly", "Leo"]
    family_names = ["Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"]

    list_of_clients = []
    _id = 100
    for index in range(0, number_to_generate):
        given_name = random.choice(given_names)
        family_name = random.choice(family_names)

        list_of_clients.append(Client(_id + index, given_name + " " + family_name))

    return list_of_clients

if __name__ == '__main__':
    for client in generate_random_clients(20):
        print(str(client))

# if __name__ == '__main__':
#     client = Client('Alex')
#     print(str(client))