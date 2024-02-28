from src.domain.book import  Book
from src.repository.memory_repository import *
from src.services.rental_service import RentalService
from src.services.undo_service import FunctionCall, Operation
from src.utilities.const import *
import copy

class BookService:
    def __init__(self, undo_service, book_repository, rental_service):
        self._book_repository = book_repository
        self._undo_service = undo_service
        self._rental_service = rental_service

    def get_undo_service(self):
        return self._undo_service

    def get_data(self):
        return self._book_repository.get_data()

    def get_dict(self):
        return dict(self._book_repository.get_dict())

    def add_book(self, book: Book):
        if not isinstance(book, Book):
            raise TypeError("Object must be an instance of id_object")

        if self._book_repository.find(book.id) is not None:
            raise TypeError("Book already exists")

        self._book_repository.add(book)
        function_redo = FunctionCall(self._book_repository.add, book)
        function_undo = FunctionCall(self._book_repository.remove, book.id)
        self._undo_service.record(Operation(function_undo, function_redo))

    def find(self, _id : int):
        return self._book_repository.find(_id)

    def remove(self, _id : int):
        book = self._book_repository.remove(_id)
        function_redo = FunctionCall(self._book_repository.remove, _id)
        function_undo = FunctionCall(self._book_repository.add, book)
        self._undo_service.record(Operation(function_undo, function_redo))

        for rental in self._rental_service.get_data():
            if rental.book.id == book.id:
                self._rental_service.remove(rental.id)

        return book

    def update(self, _id : int, book : Book):
        self._book_repository.remove(_id)
        self._book_repository.add(book)


    def search_book_by_title(self, title_search : str):
        title_search = title_search.lower()
        book_list = []
        for book in range(BOOK_START, CLIENT_START):
            if self._book_repository.find(book) != None:
                book_title = copy.deepcopy(self._book_repository.__getitem__(book).title)
                book_title = book_title.lower()
                if title_search in book_title:
                    book_list.append(self._book_repository.__getitem__(book))
        return book_list

    def search_book_by_author(self, author_search : str):
        author_search = author_search.lower()
        book_list = []
        for book in range(BOOK_START, CLIENT_START):
            if self._book_repository.find(book) != None:
                book_author = copy.deepcopy(self._book_repository.__getitem__(book).author)
                book_author = book_author.lower()
                if author_search in book_author:
                    book_list.append(self._book_repository.__getitem__(book))
        return book_list