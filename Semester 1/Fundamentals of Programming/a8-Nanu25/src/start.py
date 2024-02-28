from src.domain.rental import generate_random_rentals
from src.repository.memory_repository import MemoryRepository
from src.services.book_service import BookService
from src.services.client_service import ClientService
from src.services.rental_service import RentalService
from src.utilities.const import NUMBER_TO_GENERATE
from src.ui.ui import User_interface


if __name__ == '__main__':
    book_repository = MemoryRepository()
    client_repository = MemoryRepository()
    rentals_repository = MemoryRepository()

    book_list, client_list, rentals_list = generate_random_rentals(NUMBER_TO_GENERATE)

    for book in book_list:
        book_repository.add(book)

    for client in client_list:
        client_repository.add(client)

    for rental in rentals_list:
        rentals_repository.add(rental)

    book_service = BookService(book_repository)
    client_service = ClientService(client_repository)
    rental_service = RentalService(rentals_repository, book_repository, client_repository)

    uiStart = User_interface(book_service, client_service, rental_service)
    uiStart.Start_the_program()