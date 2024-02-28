from src.domain.client import generate_random_clients, Client
from src.repository.memory_repository import *
from src.services.undo_service import FunctionCall, Operation
from src.utilities.const import *
import copy

class ClientService:
    def __init__(self, undo_service, client_repository : MemoryRepository, rental_service):
        self._client_repository = client_repository
        self._undo_service = undo_service
        self._rental_service = rental_service

    def get_undo_service(self):
        return self._undo_service

    def get_data(self):
        return self._client_repository.get_data()

    def get_dict(self):
        return self._client_repository.get_dict()

    def add_client(self, client: Client):
        if not isinstance(client, Client):
            raise TypeError("Object must be an instance of id_object")

        if self._client_repository.find(client.id) is not None:
            raise TypeError("Client already exists")

        self._client_repository.add(client)
        function_redo = FunctionCall(self._client_repository.add, client)
        function_undo = FunctionCall(self._client_repository.remove, client.id)
        self._undo_service.record(Operation(function_undo, function_redo))

    def find(self, _id : int):
        return self._client_repository.find(_id)

    def remove(self, _id : int):
        client = self._client_repository.remove(_id)
        function_redo = FunctionCall(self._client_repository.remove, _id)
        function_undo = FunctionCall(self._client_repository.add, client)
        self._undo_service.record(Operation(function_undo, function_redo))

        for rental in self._rental_service.get_data():
            if rental.client.id == client.id:
                self._rental_service.remove(rental.id)
        return client

    def update(self, _id : int, client : Client):
        self._client_repository.remove(_id)
        self._client_repository.add(client)

    def search_client_by_name(self, client_search: str):
        client_search = client_search.lower()
        clients_list = []
        for client in range(CLIENT_START, RENTAL_START):
            if self._client_repository.find(client) != None:
                client_name = copy.deepcopy(self._client_repository.__getitem__(client).name)
                client_name = client_name.lower()
                if client_search in client_name:
                    clients_list.append(self._client_repository.__getitem__(client))
        return clients_list
