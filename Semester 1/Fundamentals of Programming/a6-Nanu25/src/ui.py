#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

from functions import *
import copy

ADD_NEW_TRANSACTION = "add"
REMOVE_EXPENSES = "remove"
REPLACE_EXPENSES = "replace"
DISPLAY_EXPENSES_HAVING_DIFFERENT_PROPERTIES = "list"
FILTER = "filter"
UNDO = "undo"

MINIMUM_LENGHT_OF_UNDO = 1
REMOVE_POSITION_RANGE = 2
REMOVE_APARTAMENT_EXPENSES = 1
REMOVE_MORE_APARTAMENTS_EXPENSES = 2
REMOVE_UTILITY_BILL = 3
DISPLAY_OPTION = 1
NONE_OF_THEM = -1

DISPLAY_ALL_APPARTAMENTS = 1
DISPLAY_AN_APPARTAMENT = 2

FILTER_BY_TYPE = 1
FILTER_BY_VALUE = 2
OPERATION_INDEX = 0

def convert_string_utility_to_int(utility_bill : str) -> int:
    if utility_bill == "water":
        return WATER
    elif utility_bill == "heating":
        return HEATING
    elif utility_bill == "electricity":
        return ELECTRICITY
    elif utility_bill == "gas":
        return GAS
    elif utility_bill == "other":
        return OTHER

    return NONE_OF_THEM

def Start_program():
    apartament_to_administrate = generate_list_of_random_apartaments()
    copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
    history_of_operations = []
    history_of_operations.append(copy_apartaments_to_administrate)

    while True:
        input_comand = input()
        input_comand = input_comand.split()

        if input_comand[OPERATION_INDEX] == ADD_NEW_TRANSACTION:
            apartament_number = int(input_comand[1])
            utility = convert_string_utility_to_int(input_comand[2])

            amount_of_money = int(input_comand[3])

            try:
                apartament_to_administrate = Add_new_transaction(apartament_number, amount_of_money, utility, apartament_to_administrate)
                copy_for_add_a_new_apartament_to_apartaments_administrate = copy.deepcopy(apartament_to_administrate)
                history_of_operations.append(copy_for_add_a_new_apartament_to_apartaments_administrate)
            except ValueError as ve:
                print(ve)

        elif input_comand[OPERATION_INDEX] == REMOVE_EXPENSES:
            if input_comand[1] in ("water", "heating", "electricity", "gas", "other"):
                utility_bill = convert_string_utility_to_int(input_comand[1])
                try:
                    apartament_to_administrate = remove_expenses_for_apartaments_for_a_specific_bill(apartament_to_administrate, utility_bill)
                    remove_expenses_copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
                    history_of_operations.append(remove_expenses_copy_apartaments_to_administrate)
                except ValueError as ve:
                    print(ve)
            else:
                first_index_of_apartament = int(input_comand[1])
                last_index_of_apartament = int(input_comand[1])
                if len(input_comand) > REMOVE_POSITION_RANGE:
                    last_index_of_apartament = int(input_comand[2])

                apartament_to_administrate = remove_expenses_for_appartaments_between_an_range(apartament_to_administrate, first_index_of_apartament, last_index_of_apartament)
                remove_range_copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
                history_of_operations.append(remove_range_copy_apartaments_to_administrate)

        elif input_comand[OPERATION_INDEX] == REPLACE_EXPENSES:
            apartament_number = int(input_comand[1])
            utility_bill = convert_string_utility_to_int(input_comand[2])
            amount_of_money = int(input_comand[3])
            try:
                apartament_to_administrate = replace_apartament_bill_with_amount(apartament_to_administrate, apartament_number, utility_bill, amount_of_money)

                replace_bill_copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
                history_of_operations.append(replace_bill_copy_apartaments_to_administrate)
            except ValueError as ve:
                print(ve)
        elif input_comand[OPERATION_INDEX] == DISPLAY_EXPENSES_HAVING_DIFFERENT_PROPERTIES:
            if len(input_comand) == DISPLAY_OPTION:
                print_apartaments_to_administrate(apartament_to_administrate)
            else:
                if input_comand[1] not in (">", "<", "="):
                    apartament_number = int(input_comand[1])
                    try:
                        print_all_expenses_for_an_apartament(apartament_to_administrate, apartament_number)
                    except ValueError as ve:
                        print(ve)
                else:
                    sign = -1
                    if input_comand[1] == "=":
                        sign = EQUAL
                    elif input_comand[1] == ">":
                        sign = HIGHER
                    elif input_comand[1] == "<":
                        sign = LOWER
                    amount_of_money = int(input_comand[2])
                    try:
                        print_all_apartaments_with_total_sum_compared_with_amount(apartament_to_administrate, amount_of_money, sign)
                    except ValueError as ve:
                        print(ve)
        elif input_comand[OPERATION_INDEX] == FILTER:
            if input_comand[1] not in ("water", "heating", "electricity", "gas", "other"):
                amount_of_money = int(input_comand[1])
                apartament_to_administrate = filter_apartaments_for_an_amouth(apartament_to_administrate, amount_of_money)

                filter_utility_bill_copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
                history_of_operations.append(filter_utility_bill_copy_apartaments_to_administrate)
            else:
                utility_bill = convert_string_utility_to_int(input_comand[1])
                try:
                    apartament_to_administrate = filter_apartaments_for_a_utility_bill(apartament_to_administrate, utility_bill)
                    filter_amount_money_copy_apartaments_to_administrate = copy.deepcopy(apartament_to_administrate)
                    history_of_operations.append(filter_amount_money_copy_apartaments_to_administrate)
                except ValueError as ve:
                    print(ve)
        elif input_comand[OPERATION_INDEX] == UNDO:
            if len(history_of_operations) > MINIMUM_LENGHT_OF_UNDO:
                history_of_operations.pop()
                apartament_to_administrate = history_of_operations[len(history_of_operations) - 1]
            else:
                print("Can't do the undo")
        else:
            print("Bye")
            break
