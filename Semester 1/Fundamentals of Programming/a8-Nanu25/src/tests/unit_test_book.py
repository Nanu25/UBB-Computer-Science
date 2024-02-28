import unittest

from src.domain.book import Book
from src.repository.memory_repository import MemoryRepository
from src.services.book_service import BookService


class TestBook(unittest.TestCase):

    def setUp(self):
        self.__book_repository = MemoryRepository()
        self.__book_service = BookService(self.__book_repository)

    def test_add_book(self):
        _id = 10
        title = "Iona"
        author = "Liviu Rebreanu"
        self.__book_service.add_book(Book(_id, title, author))

        added_book = self.__book_repository.__getitem__(_id)
        self.assertEqual(added_book.title, title)
        self.assertEqual(added_book.author, author)

    def test_duplicate_id(self):
        _id = 10
        title = "Iona"
        author = "Liviu Rebreanu"

        add_book = Book(_id, title, author)
        self.__book_service.add_book(add_book)

        self.assertEqual(_id, self.__book_repository.__getitem__(_id).id)

    def test_remove_book(self):
        _id = 10
        title = "Iona"
        author = "Liviu Rebreanu"
        add_book = Book(_id, title, author)

        self.__book_service.add_book(add_book)
        self.assertEqual(add_book, self.__book_repository.__getitem__(_id))

        self.__book_service.remove(_id)
        self.assertNotIn(add_book, self.__book_service.get_data())

    def test_update_books(self):
        _id = 10
        title = "Iona"
        author = "Liviu Rebreanu"
        add_book = Book(_id, title, author)
        self.__book_service.add_book(add_book)

        update_book = Book(10, "Amintiri din copilarie", "Ion Creanga")
        self.__book_service.remove(_id)
        self.__book_service.add_book(update_book)

        added_book = self.__book_repository.__getitem__(_id)
        self.assertEqual(added_book.title, update_book.title)
        self.assertEqual(added_book.author, update_book.author)

if __name__ == '__main__':
    unittest.main()