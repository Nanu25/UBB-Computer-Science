from src.domain.client import Client, generate_random_clients, Client
from src.domain.book import *
from datetime import date, timedelta

class Rental(id_object):
    def __init__(self, _id : int, book : Book, client : Client, rented_date : date, returned_date : date):
        super().__init__(_id)

        if not isinstance(book, Book):
            raise TypeError('Book must be of type Book')

        if not isinstance(client, Client):
            raise TypeError('Client must be of type Client')

        if not isinstance(rented_date, date):
            raise TypeError('rented_date must be of type date')

        if not isinstance(returned_date, date):
            raise TypeError('returned_date must be of type date')


        self.__book = book
        self.__client = client
        self.__rented_date = rented_date
        self.__returned_date = returned_date

    def __str__(self):
        return f"Rental id {self.id},\nBook {self.book},\nClient {self.client},\nRented date {self.rented_date}, Returned date {self.returned_date}"

    @property
    def book(self):
        return self.__book

    @property
    def client(self):
        return self.__client

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def returned_date(self):
        return self.__returned_date

    def __len__(self):
        return (self.returned_date - self.rented_date).days + 1


def generate_random_rentals(number_to_generate = NUMBER_TO_GENERATE):
    book_list = generate_random_book(NUMBER_TO_GENERATE)
    client_list = generate_random_clients(NUMBER_TO_GENERATE)
    rental_list = []
    _id = 1000

    for index in range(0, number_to_generate):
        book = random.choice(book_list)
        client = random.choice(client_list)

        start_date = date.today() + timedelta(days=random.randint(-60, -10))
        end_date = start_date + timedelta(days=random.randint(1, 10))

        rental_list.append(Rental(_id + index, book, client, start_date, end_date))

    return book_list, client_list, rental_list

if __name__ == '__main__':
    for rental in generate_random_rentals():
        print(rental)
        print('\n')