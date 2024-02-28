from src.domain.book import  Book
from src.repository.memory_repository import *
from src.utilities.const import *
import copy

class BookService:
    def __init__(self, book_repository : MemoryRepository):
        self.__book_repository = book_repository

    # def __getitem__(self, item):
    #     return self.__book_repository.__getitem__(item)

    def get_data(self):
        return self.__book_repository.get_data()

    def add_book(self, book: Book):
        if not isinstance(book, Book):
            raise TypeError("Object must be an instance of id_object")

        if self.__book_repository.find(book.id) is not None:
            raise TypeError("Book already exists")

        self.__book_repository.add(book)

    def find(self, _id : int):
        return self.__book_repository.find(_id)

    def remove(self, _id : int):
        return self.__book_repository.remove(_id)

    def print_available_books(self, available_book : list):
        for book in range(BOOK_START, CLIENT_START):
            if self.__book_repository.find(book) != None and available_book[book] == AVAILABLE:
                print(self.__book_repository.__getitem__(book))


    def search_book_by_title(self, title_search : str):
        title_search = title_search.lower()
        book_list = []
        for book in range(BOOK_START, CLIENT_START):
            if self.__book_repository.find(book) != None:
                book_title = copy.deepcopy(self.__book_repository.__getitem__(book).title)
                book_title = book_title.lower()
                if title_search in book_title:
                    book_list.append(self.__book_repository.__getitem__(book))
        return book_list

    def search_book_by_author(self, author_search : str):
        author_search = author_search.lower()
        book_list = []
        for book in range(BOOK_START, CLIENT_START):
            if self.__book_repository.find(book) != None:
                book_author = copy.deepcopy(self.__book_repository.__getitem__(book).author)
                book_author = book_author.lower()
                if author_search in book_author:
                    book_list.append(self.__book_repository.__getitem__(book))
        return book_list
