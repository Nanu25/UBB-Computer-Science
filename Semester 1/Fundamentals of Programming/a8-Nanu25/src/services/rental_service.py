from src.domain.client import Client
from src.domain.rental import generate_random_rentals, Rental
from src.repository.memory_repository import *
from src.utilities.const import *

class ClientRentalDaysDTO:
    def __init__(self, client: Client, day_count: int):
        self.__client = client
        self.__days = day_count

    @property
    def client(self):
        return self.__client

    @property
    def day_count(self):
        return self.__days

    def __lt__(self, other):
        return self.day_count <= other.day_count

    def __str__(self):
        return "rented for " + str(self.day_count) + ", clent is " + str(self.client)

    def __repr__(self):
        return str(self)



class RentalService:
    def __init__(self, rental_repository : MemoryRepository, book_repository : MemoryRepository, client_repository : MemoryRepository):
        self.__rentals_repository = rental_repository
        self.__book_repository = book_repository
        self.__client_repository = client_repository

    def __len__(self):
        return self.__rentals_repository.__len__()

    # def __getitem__(self, item):
    #     return self.__rentals_repository.__getitem__(item)

    def get_data(self):
        return self.__rentals_repository.get_data()

    def add_rental(self, rental: Rental):
        if not isinstance(rental, Rental):
            raise TypeError("Object must be an instance of id_object")

        if self.__rentals_repository.find(rental.id) is not None:
            raise TypeError("Client already exists")

        self.__rentals_repository.add(rental)

    def find(self, _id : int):
        return self.__rentals_repository.find(_id)

    def remove(self, _id : int):
        return self.__rentals_repository.remove(_id)

    def most_rented_books(self):
        rentals_list = []
        for rental in range(RENTAL_START, RENTAL_END):
            if self.__rentals_repository.find(rental) != None:
                rentals_list.append(self.__rentals_repository.__getitem__(rental))

        number_of_apparence = {}
        for rental in rentals_list:
            if rental.book not in number_of_apparence:
                number_of_apparence[rental.book] = 1
            else:
                number_of_apparence[rental.book] += 1

        number_of_apparence = sorted(number_of_apparence.items(), key=lambda x: x[1], reverse=True)

        return number_of_apparence


    def most_active_clients(self):
        clients_list = []
        for client in range(CLIENT_START, RENTAL_START):
            if self.__client_repository.find(client) != None:
                clients_list.append(self.__client_repository.__getitem__(client))

        all_rentals = []
        for rental in range(RENTAL_START, RENTAL_END):
            if self.__rentals_repository.find(rental) != None:
                all_rentals.append(self.__rentals_repository.__getitem__(rental))

        number_of_apparence = {}
        for rental in range(RENTAL_START, RENTAL_END):
            if self.__rentals_repository.find(rental) != None:
                rental_client_id = self.__rentals_repository.__getitem__(rental).client.id
                if rental_client_id not in number_of_apparence:
                    number_of_apparence[rental_client_id] = [self.__rentals_repository.__getitem__(rental)]
                else:
                    number_of_apparence[rental_client_id].append(self.__rentals_repository.__getitem__(rental))

        client_rental_days = {}
        for client_id in number_of_apparence:
            client_rental_days[client_id] = 0
            for rental in number_of_apparence[client_id]:
                client_rental_days[client_id] += len(rental)

        result = []
        for client_id in client_rental_days:
            item = ClientRentalDaysDTO(self.__client_repository.__getitem__(client_id), client_rental_days[client_id])
            result.append(item)

        result.sort(reverse=True)

        return result


    def most_rented_author(self):
        rentals_list = []
        for rental in range(RENTAL_START, RENTAL_END):
            if self.__rentals_repository.find(rental) != None:
                rentals_list.append(self.__rentals_repository.__getitem__(rental))

        number_of_apparence = {}
        for rental in rentals_list:
            if rental.book.author not in number_of_apparence:
                number_of_apparence[rental.book.author] = 1
            else:
                number_of_apparence[rental.book.author] += 1

        number_of_apparence = sorted(number_of_apparence.items(), key=lambda x: x[1], reverse=True)
        return number_of_apparence
