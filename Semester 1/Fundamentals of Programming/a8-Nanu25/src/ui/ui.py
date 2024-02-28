from datetime import date, timedelta
import random

from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import  Client, Rental
from src.services.book_service import *
from src.services.client_service import ClientService
from src.services.rental_service import *
from src.repository.memory_repository import *
from src.utilities.const import *


class User_interface:
    def __init__(self, book_service : BookService, client_service : ClientService, rental_service : RentalService):
        self.__book_service = book_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__available_book = [0] * CLIENT_START

    def print_menu(self):
        print("1 to manage books and clients")
        print("2 to rent or return a book")
        print("3 serch for books and clients")
        print("4 to create statistics")

    def manage_list_book(self):
        print("1 to add a book")
        print("2 to remove an existing book")
        print("3 to update an existing book")
        print("4 to print the book list")

    def manage_list_clients(self):
        print("1 to add a client")
        print("2 to remove an existing client")
        print("3 to update an existing client")
        print("4 to print the client list")

    def print_book_list(self):
        for book in self.__book_service.get_data():
            print(book)
    def print_client_list(self):
        for client in self.__client_service.get_data():
            print(client)
    def print_rental_list(self):
        for rental in self.__rental_service.get_data():
            print(rental)

    def Start_the_program(self):
        while True:
            self.print_menu()
            choice = int(input(">"))
            if choice == MANAGE_BOOKS_CLIENTS:
                print("1 to manage book list")
                print("2 to manage client list")
                option = int(input(">"))

                if option == MANAGE_BOOKS:
                    self.manage_list_book()
                    option = int(input(">"))
                    if option == ADD:
                        _id = int(input("Id, a integer number < 100 : "))
                        book_title = str(input("Title : "))
                        book_author = str(input("Author : "))

                        self.__book_service.add_book(Book(_id, book_title, book_author))
                    elif option == REMOVE:
                        id_to_remove = int(input("Id to remove : "))
                        self.__book_service.remove(id_to_remove)
                    elif option == UPDATE:
                        _id = int(input("Id to update (valid id < 100) : "))
                        book_title = str(input("Title : "))
                        book_author = str(input("Author : "))

                        self.__book_service.remove(_id)
                        self.__book_service.add_book(Book(_id, book_title, book_author))
                    else:
                        self.print_book_list()
                else:
                    self.manage_list_clients()
                    option = int(input(">"))
                    if option == ADD:
                        _id = int(input("Id, a integer number between 100, 1000 "))
                        client_name = str(input("Client Name : "))

                        self.__client_service.add_client(Client(_id, client_name))
                    elif option == REMOVE:
                        id_to_remove = int(input("Id to remove : "))
                        self.__client_service.remove(id_to_remove)
                    elif option == UPDATE:
                        _id = int(input("Id to update (valid id < 1000) "))
                        client_name = str(input("Client Name : "))

                        self.__client_service.remove(_id)
                        self.__client_service.add_client(Client(_id, client_name))
                    else:
                        self.__client_service.print_clients()

            elif choice == RENT_OR_RETURN_BOOK:
                print("1 for rent an availabe book")
                print("2 for return a book")
                print("3 for print rental list")
                option = int(input("> "))

                if option == RENT:
                    _id = len(self.__rental_service) + RENTAL_START
                    client_id = int(input("Client ID : "))

                    self.__book_service.print_available_books(self.__available_book)
                    book_id = int(input("Book ID : "))

                    if self.__available_book[book_id] != AVAILABLE:
                        print("Unavaible book")
                        continue

                    self.__available_book[book_id] += 1
                    client = self.__client_service.__getitem__(client_id)
                    book = self.__book_service.__getitem__(book_id)

                    rented_date = date.today()
                    returned_date = rented_date + timedelta(days=random.randint(RANDOM_DAY_START, RANDOM_DAY_END))

                    self.__rental_service.add_rental(Rental(_id, book, client, rented_date, returned_date))
                    print("The id rental is : ", _id)
                elif option == RETURN:
                    _id = int(input("Id of your rental"))
                    rental = self.__rental_service.__getitem__(_id)
                    book_id = rental.book.id
                    self.__available_book[book_id] = AVAILABLE
                    self.__rental_service.remove(_id)
                else:
                    self.print_rental_list()

            elif choice == SEARCH_BOOKS_CLIENTS:
                print("1 for search books")
                print("2 for search clients")
                option = int(input("> "))

                if option == SEARCH_BOOKS:
                    print("1 for id search")
                    print("2 for title search")
                    print("3 for author search")
                    search_option = int(input("> "))

                    if search_option == ID_SEARCH:
                        _id = int(input("Id: "))
                        book = self.__book_service.__getitem__(_id)
                        print(str(book))
                    elif search_option == TITLE_SEARCH:
                        title = str(input("Title: "))
                        book_list = self.__book_service.search_book_by_title(title)
                        for book in book_list:
                            print(book)
                    else:
                        author = str(input("Author: "))
                        book_list = self.__book_service.search_book_by_author(author)
                        for book in book_list:
                            print(book)
                else:
                    print("1 for id search")
                    print("2 for name search")
                    search_option = int(input("> "))

                    if search_option == ID_SEARCH:
                        _id = int(input("Id: "))
                        client = self.__client_service.__getitem__(_id)
                        print(str(client))
                    else:
                        name = str(input("Name: "))
                        client_list = self.__client_service.search_client_by_name(name)
                        for client in client_list:
                            print(client)

            elif choice == CREATE_STATISTICS:
                print("1 for most rented books ")
                print("2 for most active clients ")
                print("3 for most rented authors ")
                choice = int(input("> "))

                if choice == MOST_RENTED_BOOKS:
                    rentals_list = self.__rental_service.most_rented_books()
                    for rental in rentals_list:
                        print(rental[0], rental[1])
                elif choice == MOST_ACTIVE_CLIENTS:
                    rentals_list = self.__rental_service.most_active_clients()
                    for rental in rentals_list:
                        print(rental)
                else:
                    rentals_list = self.__rental_service.most_rented_author()
                    for rental in rentals_list:
                        print(rental[0], rental[1])
            else:
                print("Bye")
                break


# if __name__ == '__main__':
#     ui = User_interface()
#     ui.Start_the_program()
