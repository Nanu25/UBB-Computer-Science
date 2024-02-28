import random

from src.repository.repository_text_file_a7 import *
from src.domain.domain_a7 import *
import pickle
from src.utils.consts import FIRST_DAY, MINIM_AMOUNT, LAST_DAY, MAXIM_AMOUNT, LAST_TYPE, FIRST_TYPE


class ExpensesRepositoryBinaryFile():

    def __init__(self, new_file_name : str):
        self.__file_name = new_file_name
        self.__data = []
        self.__load_file()

    def add_new_expenses(self, new_expenses : Expenses):
        self.__data.append(new_expenses)
        self.__save_file()

    def get_all(self) -> list:
        return self.__data

    def save_all(self, expenses: list):
        self.__data = expenses
        self.__save_file()

    def __save_file(self):
        file = open(self.__file_name, "wb")
        pickle.dump(self.__data, file)
        file.close()

    def __load_file(self):
        try:
            file = open(self.__file_name, "rb")
            self.__data = pickle.load(file)
            file.close()
        except FileNotFoundError:
            print("Not found")
        except OSError:
            raise RepositoryError("Cannot start the repository")


# def generate_random_expenses(number_of_expenses: int) -> list:
#     expenses_list = []
#
#     type_of_expense = ["gas", "heat", "water", "other", "electricity", "car_tax"]
#     for i in range(0, number_of_expenses):
#         day = random.randint(FIRST_DAY, LAST_DAY)
#         amount = random.randint(MINIM_AMOUNT, MAXIM_AMOUNT)
#         type = type_of_expense[random.randint(FIRST_TYPE, LAST_TYPE)]
#         expenses_list.append(Expenses(day, amount, type))
#
#     return expenses_list

# if __name__ == "__main__":
#     binary_repository = ExpensesRepositoryBinaryFile("expenses.data")
#
#     for expenses in binary_repository.get_all():
#         print(expenses)
#
#     expenses_list = generate_random_expenses(10)
#     for expenses in expenses_list:
#         binary_repository.add_new_expenses(expenses)
