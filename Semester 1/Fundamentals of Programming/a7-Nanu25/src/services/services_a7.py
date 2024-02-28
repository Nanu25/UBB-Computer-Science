from src.repository.repository_text_file_a7 import *
from src.repository.repository_binary_file_a7 import *
from src.domain.domain_a7 import *
import copy

from src.utils.consts import  MINIMUM_NUMBER_FOR_UNDO


class ServiceClass():
    def __init__(self, repository):  # incapsulare
        self.__repository = repository
        self.__history_of_operations = []
        self.__update_history()

    def get_all(self) -> list:
        return self.__repository.get_all()

    def __update_history(self):
        self.__history_of_operations.append(copy.deepcopy(self.__repository.get_all()))

    def add_new_expenses(self,  day : int, amount : int, type : str):
        self.__repository.add_new_expenses(Expenses(day, amount, type))
        self.__update_history()

    def filter_only_expenses_with_amount_above_a_value(self, value : int):
        filtered_expenses_list = copy.deepcopy(self.__repository.get_all())
        index = 0
        while index < len(filtered_expenses_list):
            if filtered_expenses_list[index].amount < value:
                filtered_expenses_list.pop(index)
            else:
                index += 1
        self.__repository.save_all(filtered_expenses_list)
        self.__update_history()

    def undo_last_operation(self):
        if len(self.__history_of_operations) == MINIMUM_NUMBER_FOR_UNDO:
            raise ValueError("Imposibile to undo")

        self.__history_of_operations.pop()
        self.__repository.save_all(self.__history_of_operations[-1])


"""if __name__ == "__main__":
    expenses_list = generate_random_expenses(10)
    #print_expenses_list(expenses_list)

    print("")
    expenses_list = filter_only_expenses_with_amount_above_a_value(expenses_list, 50)
    #print_expenses_list(expenses_list)"""