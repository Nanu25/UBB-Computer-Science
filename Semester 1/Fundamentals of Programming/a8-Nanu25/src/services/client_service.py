from src.domain.client import generate_random_clients, Client
from src.repository.memory_repository import *
from src.utilities.const import *
import copy

class ClientService:
    def __init__(self, client_repository : MemoryRepository):
        self.__client_repository = client_repository

    # def __getitem__(self, item):
    #     return self.__client_repository.__getitem__(item)

    def get_data(self):
        return self.__client_repository.get_data()

    def add_client(self, client: Client):
        if not isinstance(client, Client):
            raise TypeError("Object must be an instance of id_object")

        if self.__client_repository.find(client.id) is not None:
            raise TypeError("Client already exists")

        self.__client_repository.add(client)

    def find(self, _id : int):
        return self.__client_repository.find(_id)

    def remove(self, _id : int):
        return self.__client_repository.remove(_id)

    def search_client_by_name(self, client_search: str):
        client_search = client_search.lower()
        client_list = []
        for client in range(CLIENT_START, RENTAL_START):
            if self.__client_repository.find(client) != None:
                client_name = copy.deepcopy(self.__client_repository.__getitem__(client).name)
                client_name = client_name.lower()
                if client_search in client_name:
                    client_list.append(self.__client_repository.__getitem__(client))

        return client_list
