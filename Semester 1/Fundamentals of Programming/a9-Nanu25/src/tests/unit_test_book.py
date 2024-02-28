import unittest

from src.domain.book import Book
from src.repository.memory_repository import MemoryRepository
from src.services.book_service import BookService
from src.services.undo_service import UndoService


class TestBook(unittest.TestCase):

    def setUp(self):
        self.__book_repository = MemoryRepository()
        self.__rentals_repository = MemoryRepository()
        self.__undo_service = UndoService()
        self.__book_service = BookService(self.__undo_service, self.__book_repository, self.__rentals_repository)

    def test_add_book(self):
        _id = 10
        title = "Ion"
        author = "Liviu Rebreanu"
        self.__book_service.add_book(Book(_id, title, author))

        added_book = self.__book_service.get_dict()[_id]
        self.assertIn(added_book, self.__book_service.get_data())

    def test_remove_book(self):
        _id = 10
        title = "Iona"
        author = "Liviu Rebreanu"
        add_book = Book(_id, title, author)

        self.__book_service.add_book(add_book)
        self.assertIn(add_book, self.__book_service.get_data())

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

        added_book = self.__book_service.get_dict()[_id]
        self.assertIn(added_book, self.__book_service.get_data())

    def test_undo_book(self):
        book = Book(10, "Amintiri din copilarie", "Ion Creanga")
        self.__book_service.add_book(book)
        self.assertEqual(self.__book_service.find(10),  book)

        self.__book_service.get_undo_service().undo()
        self.assertNotIn(book, self.__book_service.get_data())

    def test_redo_book(self):
        book = Book(10, "Amintiri din copilarie", "Ion Creanga")
        self.__book_service.add_book(book)

        self.__book_service.get_undo_service().undo()
        self.__book_service.get_undo_service().redo()
        self.assertIn(book, self.__book_service.get_data())

if __name__ == '__main__':
    unittest.main()