from src.domain.domain_a7 import *
from src.services.services_a7 import *

class RepositoryError(Exception):

    def __init__(self, error_message : str):
        self.__message = error_message

    @property
    def message(self):
        return self.__message

    def __str__(self):
        return self.__message


class ExpensesTextFileRepository():
    def __init__(self, new_file_name : str):
        self.__file_name = new_file_name
        self.__expenses_list = []
        self.__load_file()

    def add_new_expenses(self, new_expenses : Expenses):
        self.__expenses_list.append(new_expenses)
        self.__save_file()

    def save_all(self, expenses: list):
        self.__expenses_list = expenses
        self.__save_file()

    def __save_file(self):
        with open(self.__file_name, "w") as file:
            for expenses in self.__expenses_list:
                file.write(expenses.file_format() + "\n")
        file.close()

    def __load_file(self):
        with open(self.__file_name, "r") as file:
            for line in file.readlines():
                line = line.strip()
                elements_from_file = line.split(' ')
                day = int(elements_from_file[0])
                amount = int(elements_from_file[1])
                type = elements_from_file[2]
                self.__expenses_list.append(Expenses(day, amount, type))
        file.close()

    def __str__(self):
        return str(self.__expenses_list)

    def get_all(self) -> list:
        return self.__expenses_list





#expenses_memory = ExpensesTextFileRepository("expenses.data")

"""expenses_list = generate_random_expenses(NUMBER_TO_GENERATE)
for expenses in expenses_list:
    expenses_memory.add_new_expenses(expenses)

#Write in a file
file = open("expenses.data", "w")
with open("expenses.data", "w") as file:
    for index in range(0, NUMBER_TO_GENERATE):
        file.write(str(expenses_memory.get_all()[index]))
        file.write("\n")
file.close()

#read from a file
with open("expenses.data", "r") as  file:
    for index in range(0, NUMBER_TO_GENERATE):
        expenses = file.read()
        if expenses != "\n":
            expenses_memory.add_new_expenses(expenses)
file.close()"""

"""for index in range(0, len(expenses_memory.get_all())):
    print(str(expenses_memory.get_all()[index]))"""