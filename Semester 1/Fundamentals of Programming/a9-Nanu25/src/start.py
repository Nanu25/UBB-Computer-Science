from src.domain.rental import generate_random_rentals
from src.repository.binary_file.binary_file_rentals import BinaryFileRepoRentals
from src.repository.binary_file.binary_file_repo_books import BinaryFileRepoBooks
from src.repository.binary_file.binary_file_repo_client import BinaryFileRepoClients
from src.repository.memory_repository import MemoryRepository
from src.repository.text_file.text_file_clients import TextFileRepositoryClient
from src.repository.text_file.text_file_repo_books import TextFileRepositoryBook
from src.repository.text_file.text_file_repo_rentals import TextFileRepositoryRental
from src.services.book_service import BookService
from src.services.client_service import ClientService
from src.services.rental_service import RentalService
from src.services.undo_service import UndoService
from src.utilities.const import NUMBER_TO_GENERATE
from src.ui.ui import User_interface


def Choose_repository():
    # if i put "" in the settings file it will be a error at parsing
    with open("repository_settings.properties", "r") as file:
        settings = file.readlines()
        settings = [setting.replace("", '') for setting in settings]
        settings = [setting.strip() for setting in settings]
        settings = [setting.split("=") for setting in settings]
        settings_dict = {}
        for i in range(len(settings)):
            settings_dict[settings[i][0].strip()] = settings[i][1].strip()

        if settings_dict["repository"] == "inmemory":
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

            return book_repository, client_repository, rentals_repository
        elif settings_dict["repository"] == "textfiles":
            book_repository = TextFileRepositoryBook(settings_dict["books"])
            client_repository = TextFileRepositoryClient(settings_dict["clients"])
            rentals_repository = TextFileRepositoryRental(settings_dict["rentals"])
            return book_repository, client_repository, rentals_repository
        else:
            book_repository = BinaryFileRepoBooks(settings_dict["books"])
            client_repository = BinaryFileRepoClients(settings_dict["clients"])
            rentals_repository = BinaryFileRepoRentals(settings_dict["rentals"])
            return book_repository, client_repository, rentals_repository

if __name__ == '__main__':

    book_repository, client_repository, rentals_repository = Choose_repository()

    undo_service = UndoService()
    rental_service = RentalService(undo_service, rentals_repository, book_repository, client_repository)
    book_service = BookService(undo_service, book_repository, rental_service)
    client_service = ClientService(undo_service, client_repository, rental_service)

    uiStart = User_interface(book_service, client_service, rental_service)
    uiStart.Start_the_program()