import copy

from src.repository.memory_repository import MemoryRepository
from src.repository.repository_binary_file_a7 import *
from src.services.services_a7 import ServiceClass

EXIT_APP = 0
ADD_NEW_EXPENSES = 1
DISPLAY_THE_LIST = 2
FILTER_THE_LIST = 3
UNDO_LAST_OPERATION = 4
MEMORY_REPOSITORY = 1
FILE_REPOSITORY = 2
BINARY_REPOSITORY = 3
DAY = 0
EXPENSES_AMOUNT = 1
EXPENSES_TYPE = 2


class UserInterface:
    def __init__(self):
        self.__service = None

    def print_menu(self):
        print("Choose a option from below")
        print("1 for add a new expenses")
        print("2 for display the list of expenses")
        print("3 for filter the list of expenses above a value")
        print("4 undo the last operation")
        print("0 exit the app")

    def print_expenses_list(self):
        for expenses in self.__service.get_all():
            print(str(expenses))
        print("")

    def start_the_program(self):
        print("Choose what repository do you want to use: ")
        print("1 for Memory Repository")
        print("2 for Text File Repository")
        print("3 for Binary File Repository")
        repository_option = int(input(">"))

        if repository_option == MEMORY_REPOSITORY:
            repository = MemoryRepository()
        elif repository_option == FILE_REPOSITORY:
            repository = ExpensesTextFileRepository("expenses.data")
        elif repository_option == BINARY_REPOSITORY:
            repository = ExpensesRepositoryBinaryFile("myexpenses.data")
        else:
            raise ValueError("Invalid repository type")

        self.__service = ServiceClass(repository)

        while True:
            try:
                self.print_menu()
                option = int(input(">"))
                if option == ADD_NEW_EXPENSES:
                    day = int(input("Tell me a day between 1 and 30 "))
                    amount = int(input("Tell me an amount of money "))
                    expenses = input("Tell me an expenses ")
                    self.__service.add_new_expenses(day, amount, expenses)
                elif option == DISPLAY_THE_LIST:
                    self.print_expenses_list()
                elif option == FILTER_THE_LIST:
                    amount = int(input("Tell me the amount of money"))
                    self.__service.filter_only_expenses_with_amount_above_a_value(amount)
                elif option == UNDO_LAST_OPERATION:
                    self.__service.undo_last_operation()
                elif option == EXIT_APP:
                    print("Bye!")
                    break
                else:
                    raise ValueError("Invalid option")
            except ValueError as ve:
                print(ve)


if __name__ == "__main__":
    ui = UserInterface()
    ui.start_the_program()
