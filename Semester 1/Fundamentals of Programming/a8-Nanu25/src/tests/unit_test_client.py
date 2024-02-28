import unittest

from src.domain.client import Client
from src.repository.memory_repository import MemoryRepository
from src.services.client_service import ClientService


class TestClient(unittest.TestCase):

    def setUp(self):
        self.__client_repository = MemoryRepository()
        self.__client_service = ClientService(self.__client_repository)

    def test_add_client(self):
        _id = 101
        name = "Popescu Ion"
        self.__client_service.add_client(Client(_id, name))

        added_client = self.__client_repository.__getitem__(_id)
        self.assertEqual(added_client.name, name)

    def test_duplicate_id(self):
        _id = 101
        name = "Popescu Ion"
        self.__client_service.add_client(Client(_id, name))
        self.assertEqual(_id, self.__client_repository.__getitem__(_id).id)

    def test_remove_client(self):
        _id = 101
        name = "Popescu Ion"
        add_client = Client(_id, name)
        self.__client_service.add_client(add_client)

        self.assertEqual(add_client, self.__client_repository.__getitem__(_id))
        self.__client_service.remove(_id)
        self.assertNotIn(add_client, self.__client_repository)

    def test_update_books(self):
        _id = 101
        name = "Popescu Ion"
        add_client = Client(_id, name)
        self.__client_service.add_client(add_client)

        update_client = Client(101, "Ion Creanga")
        self.__client_service.remove(_id)
        self.__client_service.add_client(update_client)

        added_client = self.__client_repository.__getitem__(_id)
        self.assertEqual(added_client.name, update_client.name)

if __name__ == '__main__':
    unittest.main()