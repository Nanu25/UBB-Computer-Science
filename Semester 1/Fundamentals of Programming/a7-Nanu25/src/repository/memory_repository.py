import random

from src.domain.domain_a7 import Expenses
from src.utils.consts import *

class MemoryRepository:
    def generate_random_expenses(self, number_of_expenses: int) -> list:
        expenses_list = []

        type_of_expense = ["gas", "heat", "water", "other", "electricity", "car_tax"]
        for i in range(0, number_of_expenses):
            day = random.randint(FIRST_DAY, LAST_DAY)
            amount = random.randint(MINIM_AMOUNT, MAXIM_AMOUNT)
            type = type_of_expense[random.randint(FIRST_TYPE, LAST_TYPE)]
            expenses_list.append(Expenses(day, amount, type))

        return expenses_list
    def __init__(self):
        self.__expenses_list = self.generate_random_expenses(NUMBER_TO_GENERATE)

    def add_new_expenses(self, new_expenses : Expenses):
        self.__expenses_list.append(new_expenses)

    def get_all(self) -> list:
        return self.__expenses_list

    def save_all(self, expenses: list):
        self.__expenses_list = expenses
