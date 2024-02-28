#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import copy
import random
from random import randint

MINIMUM_INDEX = 1
MAXIMUM_INDEX = 20
NO_AMOUNT = 0
WATER = 1
HEATING = 2
ELECTRICITY = 3
GAS = 4
OTHER = 5
TOTAL = 6
NUMBER_OF_APARTAMENTS_STARTUP = 10
MAX_APARTAMENT = 100
FIRST_UTILITY = 1
LAST_UTILITY = 6
EQUAL = 1
HIGHER = 2
LOWER = 3

def generate_list_of_random_apartaments() -> dict:
    current_number_of_apartaments = NO_AMOUNT
    apartaments_to_administrate = {}
    while current_number_of_apartaments < NUMBER_OF_APARTAMENTS_STARTUP:
        number = randint(MINIMUM_INDEX, MAXIMUM_INDEX)
        if number in apartaments_to_administrate:
            continue
        else:
            water_bill = random.randint(0, 100)
            heating_bill = random.randint(0, 100)
            electricity_bill = random.randint(0, 100)
            gas_bill = random.randint(0, 100)
            other_bill = random.randint(0, 100)
            apartaments_to_administrate[number] = {WATER : water_bill, HEATING : heating_bill, ELECTRICITY : electricity_bill, GAS : gas_bill, OTHER : other_bill, TOTAL : water_bill + heating_bill + electricity_bill + gas_bill + other_bill}
            current_number_of_apartaments += 1
    return apartaments_to_administrate


def print_apartaments_to_administrate(apartament_to_administrate : dict):
    for apartament in range(0, MAX_APARTAMENT):
        if apartament in apartament_to_administrate:
            print("Number of apartament: ", apartament)
            print("Water: ", apartament_to_administrate[apartament][WATER]," RON")
            print("Heating", apartament_to_administrate[apartament][HEATING]," RON")
            print("Electricity", apartament_to_administrate[apartament][ELECTRICITY]," RON")
            print("Gas:", apartament_to_administrate[apartament][GAS]," RON")
            print("Other:", apartament_to_administrate[apartament][OTHER]," RON")
            print("")

def print_all_expenses_for_an_apartament(apartament_to_administrate : dict, number_of_apartament : int):
    if number_of_apartament not in apartament_to_administrate:
        raise ValueError("This apartament is not in the list")

    print("Number of apartament: ", number_of_apartament)
    print("Water: ", apartament_to_administrate[number_of_apartament][WATER], " RON")
    print("Heating", apartament_to_administrate[number_of_apartament][HEATING], " RON")
    print("Electricity", apartament_to_administrate[number_of_apartament][ELECTRICITY], " RON")
    print("Gas:", apartament_to_administrate[number_of_apartament][GAS], " RON")
    print("Other:", apartament_to_administrate[number_of_apartament][OTHER], " RON")
    print("")

def print_all_apartaments_with_total_sum_compared_with_amount(apartament_to_administrate : dict, amount : int, sign_of_comparison : int):
    if sign_of_comparison not in (EQUAL, HIGHER, LOWER):
        raise  ValueError("Invalid comparison")

    if sign_of_comparison == EQUAL:
        for apartament in range(0, MAX_APARTAMENT):
            if apartament in apartament_to_administrate:
                if apartament_to_administrate[apartament][TOTAL] == amount:
                    print("Apartament ", apartament, "has the total expenses = ", amount)
    elif sign_of_comparison == HIGHER:
        for apartament in range(0, MAX_APARTAMENT):
            if apartament in apartament_to_administrate:
                if apartament_to_administrate[apartament][TOTAL] > amount:
                    print("Apartament ", apartament, "has the total expenses > ", amount)
    else:
        for apartament in range(0, MAX_APARTAMENT):
            if apartament in apartament_to_administrate:
                if apartament_to_administrate[apartament][TOTAL] < amount:
                    print("Apartament ", apartament, "has the total expenses < ", amount)

def filter_apartaments_for_a_utility_bill(apartament_to_administrate : dict, utility_bill : int) -> dict:
    if utility_bill not in (WATER, HEATING, ELECTRICITY, GAS, OTHER):
        raise ValueError("This type is invalid")

    filter_utility_copy_of_apartaments = copy.deepcopy(apartament_to_administrate)
    for apartament in range(0, MAX_APARTAMENT):
        if apartament in filter_utility_copy_of_apartaments:
            for utility in range(FIRST_UTILITY, LAST_UTILITY):
                if utility != utility_bill:
                    filter_utility_copy_of_apartaments[apartament][TOTAL] -= filter_utility_copy_of_apartaments[apartament][utility]
                    filter_utility_copy_of_apartaments[apartament][utility] = NO_AMOUNT

    return filter_utility_copy_of_apartaments

def filter_apartaments_for_an_amouth(apartament_to_administrate : dict, amount : int) -> dict:
    filter_amouth_money_copy_of_apartaments = copy.deepcopy(apartament_to_administrate)
    for apartament in range(0, MAX_APARTAMENT):
        if apartament in filter_amouth_money_copy_of_apartaments:
            for price in range(FIRST_UTILITY, LAST_UTILITY):
                if  filter_amouth_money_copy_of_apartaments[apartament][price] > amount:
                    filter_amouth_money_copy_of_apartaments[apartament][TOTAL] -= filter_amouth_money_copy_of_apartaments[apartament][price]
                    filter_amouth_money_copy_of_apartaments[apartament][price] = NO_AMOUNT

    return filter_amouth_money_copy_of_apartaments

def Add_new_transaction(number_of_apartamet : int, amount_of_money : int, utility_bill : int, apartament_to_administrate : dict) -> dict:
    if utility_bill not in (WATER, HEATING, ELECTRICITY, GAS, OTHER):
        raise ValueError("Invalid transaction")

    new_list_for_apartaments = copy.deepcopy(apartament_to_administrate)
    if number_of_apartamet not in new_list_for_apartaments:
        new_list_for_apartaments[number_of_apartamet] = {WATER : NO_AMOUNT, HEATING : NO_AMOUNT, ELECTRICITY : NO_AMOUNT, GAS : NO_AMOUNT, OTHER : NO_AMOUNT, TOTAL : NO_AMOUNT}

    new_list_for_apartaments[number_of_apartamet][utility_bill] += amount_of_money
    new_list_for_apartaments[number_of_apartamet][TOTAL] += amount_of_money
    return new_list_for_apartaments

def remove_expenses_for_appartaments_between_an_range(apartaments_to_administrate : dict, start_apartament : int, end_apartament : int) -> dict:
    if start_apartament > end_apartament:
        start_apartament, end_apartament = end_apartament, start_apartament

    remove_apartament_copy_of_apartaments = copy.deepcopy(apartaments_to_administrate)
    for i in range(start_apartament, end_apartament + 1):
        if i in remove_apartament_copy_of_apartaments:
            remove_apartament_copy_of_apartaments[i] = {WATER : NO_AMOUNT, HEATING : NO_AMOUNT, ELECTRICITY : NO_AMOUNT, GAS : NO_AMOUNT, OTHER : NO_AMOUNT, TOTAL : NO_AMOUNT}

    return  remove_apartament_copy_of_apartaments

def remove_expenses_for_apartaments_for_a_specific_bill(apartaments_to_administrate : dict, utility_bill : int) -> dict:
    if utility_bill not in (WATER, HEATING, ELECTRICITY, GAS, OTHER):
       raise ValueError("This bill does'n exist \n")

    remove_expensess_copy_of_apartaments = copy.deepcopy(apartaments_to_administrate)
    for i in range(0, MAX_APARTAMENT):
        if i in remove_expensess_copy_of_apartaments:
            remove_expensess_copy_of_apartaments[i][TOTAL] -= remove_expensess_copy_of_apartaments[i][utility_bill]
            remove_expensess_copy_of_apartaments[i][utility_bill] = NO_AMOUNT

    return  remove_expensess_copy_of_apartaments


def replace_apartament_bill_with_amount(apartaments_to_administrate : dict, number_of_apartament : int,  utility_bill : int, amount : int) -> dict:
    if utility_bill not in (WATER, HEATING, ELECTRICITY, GAS, OTHER):
        raise ValueError("This bill does'n exist \n")

    if number_of_apartament not in apartaments_to_administrate:
        raise ValueError("This apartament does'n exist \n")

    replace_apartament_bill_copy_of_apartaments = copy.deepcopy(apartaments_to_administrate)
    replace_apartament_bill_copy_of_apartaments[number_of_apartament][TOTAL] +=  apartaments_to_administrate[number_of_apartament][utility_bill] + amount
    replace_apartament_bill_copy_of_apartaments[number_of_apartament][utility_bill] = amount
    return replace_apartament_bill_copy_of_apartaments

def undo_the_last_operation(history_for_last_operation : list) -> dict:
    apartaments_to_administrate = history_for_last_operation[len(history_for_last_operation) - 1]
    return apartaments_to_administrate
