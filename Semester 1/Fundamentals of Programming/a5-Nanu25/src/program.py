#
# Write the implementation for A5 in this file
#

ADD_NUMBER = 1
PRINT_THE_LIST = 2
DISPLAY_THE_SUBARRAY_WITH_NUMBERS_MODULE_IN_0_10_OR_LENGHT_OF_ALTERNATING_SUBSEQUENCE= 3
EXIT = 4
STARTUP_DIMENSION = 10
LEFT_VALUE_INTERVAL = 0
RIGHT_VALUE_INTERVAL = 10
TUPLE_IMPLEMENTATION = 1
DICTIONARY_IMPLEMENTATION = 2
FIRST_PROBLEM = 1
import math

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def modulus_tuple(complex_number : tuple) -> float:
    return math.sqrt(complex_number[0] ** 2 + complex_number[1] ** 2)

def create_complex_tuple_version(real_part : int, imaginary_part : int) -> tuple:
    return (real_part, imaginary_part)

import random
def generate_startup_numbers() -> tuple:
    complex_numbers = []

    # z = a + bi
    for i in range(STARTUP_DIMENSION):
        real_part = random.randint(-10, 10)
        imaginary_part = random.randint(-10, 10)
        complex_numbers.append(create_complex_tuple_version(real_part, imaginary_part))

    return complex_numbers

def convert_complex_to_string_tuple(complex_number : tuple) -> str:
    sign_imaginary = ""
    if complex_number[1] > 0:
        sign_imaginary = '+'

    if complex_number[1] == 0:
        return  str(complex_number[0])

    if complex_number[0] == 0:
        if complex_number[1] == 1:
            return "i"
        if complex_number[1] == -1:
            return "-i"

        return  str(complex_number[1]) + "i"

    if complex_number[1] == 1:
        return str(complex_number[0]) + "+i"

    if complex_number[1] == -1:
        return str(complex_number[0]) + "-i"

    return str(complex_number[0]) + sign_imaginary + str(complex_number[1]) + "i"

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def modulus_dictionary(complex_number : dict) -> float:
    return math.sqrt(complex_number["real_part"] ** 2 + complex_number["imaginary_part"] ** 2)

def create_complex_dictionary(real_part : int, imaginary_part : int) -> dict:
    return {"real_part" : real_part, "imaginary_part" : imaginary_part}

def generate_startup_numbers_dictionary() -> list:
    complex_numbers = []

    #z = a + bi
    for i in range(STARTUP_DIMENSION):
        real_part = random.randint(-10, 10)
        imaginary_part = random.randint(-10, 10)
        complex_numbers.append(create_complex_dictionary(real_part, imaginary_part))

    return complex_numbers


def convert_complex_to_string_dictionary(complex_number : dict) -> str:
    sign_imaginary = ""
    if complex_number["imaginary_part"] > 0:
        sign_imaginary = '+'

    if complex_number["imaginary_part"] == 0:
        return  str(complex_number["real_part"])

    if complex_number["real_part"] == 0:
        if complex_number["imaginary_part"] == 1:
            return "i"
        if complex_number["imaginary_part"] == -1:
            return "-i"

        return  str(complex_number["imaginary_part"]) + "i"

    if complex_number["imaginary_part"] == 1:
        return str(complex_number["real_part"]) + "+i"

    if complex_number["imaginary_part"] == -1:
        return str(complex_number["real_part"]) + "-i"

    return str(complex_number["real_part"]) + sign_imaginary + str(complex_number["imaginary_part"]) + "i"

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def Lenght_of_the_longest_subarray_with_number_modulus_in_0_10_dictionary(complex_numbers_dictionary : dict):
    maxim_lenght = 0
    actual_lenght = 0
    left_index = 0
    right_index = 0
    index = 0

    for i in complex_numbers_dictionary:
        modulus = modulus_dictionary(i)
        if LEFT_VALUE_INTERVAL <= modulus and modulus <= RIGHT_VALUE_INTERVAL:
            actual_lenght += 1
        else:
            actual_lenght = 0

        if actual_lenght > maxim_lenght:
            maxim_lenght = actual_lenght
            left_index = index - actual_lenght + 1
            right_index = index

        index += 1

    return (maxim_lenght, left_index, right_index)


def Lenght_of_the_longest_subarray_with_number_modulus_in_0_10_tuple(complex_numbers_tuple : list):
    maxim_lenght = 0
    actual_lenght = 0
    left_index = 0
    right_index = 0
    index = 0

    for i in complex_numbers_tuple:
        modulus = modulus_tuple(i)
        if LEFT_VALUE_INTERVAL <= modulus and modulus <= RIGHT_VALUE_INTERVAL:
            actual_lenght += 1
        else:
            actual_lenght = 0

        if actual_lenght > maxim_lenght:
            maxim_lenght = actual_lenght
            left_index = index - actual_lenght + 1
            right_index = index

        index += 1

    return (maxim_lenght, left_index, right_index)

def Lenght_of_the_longest_alternating_subsequence_tuple(complex_numbers_tuple : list) -> int:
    #longest_alternating_subsequence[i][0] = the longest alternating subsequence that end on position i with an element greater than the prev one.
    #longest_alternating_subsequence[i][1] = the longest alternating subsequence that end on position i with an element smaller than the prev one.
    longest_alternating_subsequence = [[0 for i in range(2)] for j in range(len(complex_numbers_tuple))]

    for i in range(len(complex_numbers_tuple)):
        longest_alternating_subsequence[i][0], longest_alternating_subsequence[i][1] = 1, 1

    maxim_lenght = 1
    for i in range(1, len(complex_numbers_tuple)):
        for j in range(0, i):
            number_modulus = modulus_tuple(complex_numbers_tuple[i])

            # if module(j) is lower i am interess in the subsequence that finish with a value lower than prev. one
            if (modulus_tuple(complex_numbers_tuple[j]) < number_modulus and longest_alternating_subsequence[i][0] < longest_alternating_subsequence[j][1] + 1):
                longest_alternating_subsequence[i][0] = longest_alternating_subsequence[j][1] + 1

            if (modulus_tuple(complex_numbers_tuple[j]) > number_modulus and longest_alternating_subsequence[i][1] < longest_alternating_subsequence[j][0] + 1):
                longest_alternating_subsequence[i][1] = longest_alternating_subsequence[j][0] + 1

            maxim_lenght = max(longest_alternating_subsequence[i][0], longest_alternating_subsequence[i][1], maxim_lenght)

    return maxim_lenght

def Lenght_of_the_longest_alternating_subsequence_dictionary(complex_numbers_dictionary : list) -> int:
    #longest_alternating_subsequence[i][0] = the longest alternating subsequence that end on position i with an element greater than the prev one.
    #longest_alternating_subsequence[i][1] = the longest alternating subsequence that end on position i with an element smaller than the prev one.

    longest_alternating_subsequence = [[0 for i in range(2)] for j in range(len(complex_numbers_dictionary))]

    for i in range(len(complex_numbers_dictionary)):
        longest_alternating_subsequence[i][0], longest_alternating_subsequence[i][1] = 1, 1

    maxim_lenght = 1
    for i in range(1, len(complex_numbers_dictionary)):
        for j in range(0, i):
            number_modulus = modulus_dictionary(complex_numbers_dictionary[i])

            #if module(j) is lower i am interess in the subsequence that finish with a value lower than prev. one
            if (modulus_dictionary(complex_numbers_dictionary[j]) < number_modulus and longest_alternating_subsequence[i][0] < longest_alternating_subsequence[j][1] + 1):
                longest_alternating_subsequence[i][0] = longest_alternating_subsequence[j][1] + 1

            # if module(j) is greater i am interess in the subsequence that finish with a value greater than prev. one
            if (modulus_dictionary(complex_numbers_dictionary[j]) > number_modulus and longest_alternating_subsequence[i][1] < longest_alternating_subsequence[j][0] + 1):
                longest_alternating_subsequence[i][1] = longest_alternating_subsequence[j][0] + 1

            maxim_lenght = max(longest_alternating_subsequence[i][0], longest_alternating_subsequence[i][1], maxim_lenght)

    return maxim_lenght

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def read_complex_number() -> tuple:
    real_part_to_return = None
    imaginary_part_to_return = None
    try:
        print("Enter a complex number in the form 'a+bi':")
        input_complex_number = input("z = ")

        #if a has a minus i delete them so i can easily split
        sign_real_part = ""
        if input_complex_number[0] == '-':
            sign_real_part = '-'
            input_complex_number = input_complex_number[1:]

        #find the sign of b
        sign_complex_part = "+"
        for i in range(0, len(input_complex_number)):
            if input_complex_number[i] == '-':
                sign_complex_part = '-'

        # Splitting the real and imaginary parts
        real_part, imaginary_part = input_complex_number.split(sign_complex_part)

        # Extracting numerical values
        real_part_to_return = int(real_part)
        if sign_real_part == '-':
            real_part_to_return = -real_part_to_return

        imaginary_part_to_return = int(imaginary_part[:-1])
        if sign_complex_part == '-':
            imaginary_part_to_return = -imaginary_part_to_return

    except ValueError: print("Invalid input. Please enter a valid complex number.")

    return (real_part_to_return, imaginary_part_to_return)

def Print_modulus_tuple(complex_number : list):
    for i in complex_number:
        print(modulus_tuple(i))

def Print_modulus_dictionary(complex_number : list):
    for i in complex_number:
        print(modulus_dictionary(i))

def Print_complex_list_tuple(complex_number : list, left_index : int, right_index : int):
    for i in range(left_index, right_index):
        print(convert_complex_to_string_tuple(complex_number[i]))

def Print_complex_list_dictionary(complex_number : list, left_index : int, right_index : int):
    for i in range(left_index, right_index):
        print(convert_complex_to_string_dictionary(complex_number[i]))

def Print_menu():
    print("")
    print("1 if you want to read a complex number from the console")
    print("2 if you want to display the entire list of complex numbers")
    print("3 if you want to display a sequence of numbers with module in [0, 10] or the lenght of the longest alternating subsequence")
    print("4 for exit")

def Start_program():
    print("1 for tuple implementation")
    print("2 for dict implementation")
    choise = int(input(">"))

    complex_numbers_tuple = []
    complex_numbers_dictionary = []

    if choise == TUPLE_IMPLEMENTATION:
        complex_numbers_tuple = generate_startup_numbers()
    else:
        complex_numbers_dictionary = generate_startup_numbers_dictionary()


    while True:
        Print_menu()
        option = int(input(">"))

        if option == ADD_NUMBER:
            #real_part = int(input("Write the real part of the number"))
            #imaginary_part = int(input("Write the imaginary part of the number")

            complex_number = ()
            complex_number = read_complex_number()

            if complex_number[0] == None or complex_number[1] == None:
                continue

            real_part = complex_number[0]
            imaginary_part = complex_number[1]
            if choise == TUPLE_IMPLEMENTATION:
                complex_numbers_tuple.append(create_complex_tuple_version(real_part, imaginary_part))
            else:
                complex_numbers_dictionary.append(create_complex_dictionary(real_part, imaginary_part))

        elif option == PRINT_THE_LIST:
            if choise == TUPLE_IMPLEMENTATION:
                Print_complex_list_tuple(complex_numbers_tuple, 0, len(complex_numbers_tuple))
            else:
                Print_complex_list_dictionary(complex_numbers_dictionary, 0, len(complex_numbers_dictionary))

        elif option == DISPLAY_THE_SUBARRAY_WITH_NUMBERS_MODULE_IN_0_10_OR_LENGHT_OF_ALTERNATING_SUBSEQUENCE:
            print("")
            print("1 for lenght and elements of a longest subarray of numbers where each number's modulus is in the [0, 10]")
            print("2 for the lenght of the longest alternating subsequence")
            problem_option = int(input(">"))

            if problem_option == FIRST_PROBLEM:
                answer = ()
                if choise == TUPLE_IMPLEMENTATION:
                    answer = Lenght_of_the_longest_subarray_with_number_modulus_in_0_10_tuple(complex_numbers_tuple)
                else:
                    answer = Lenght_of_the_longest_subarray_with_number_modulus_in_0_10_dictionary(complex_numbers_dictionary)

                print("The lenght of a longest subarray of numbers that have the modulus between [0, 10] is = ", answer[0])

                if choise == TUPLE_IMPLEMENTATION:
                    Print_complex_list_tuple(complex_numbers_tuple, answer[1], answer[2] + 1)
                else:
                    Print_complex_list_dictionary(complex_numbers_dictionary, answer[1], answer[2] + 1)

            else:
                answer = 0
                if choise == TUPLE_IMPLEMENTATION:
                    answer = Lenght_of_the_longest_alternating_subsequence_tuple(complex_numbers_tuple)
                    Print_modulus_tuple(complex_numbers_tuple)
                else:
                    answer = Lenght_of_the_longest_alternating_subsequence_dictionary(complex_numbers_dictionary)
                    Print_modulus_dictionary(complex_numbers_dictionary)

                print("")
                print("The lenght of the longest alternating subsequence is = ", answer)
        else:
            print("Good bye!")
            break


if __name__ == "__main__":
    Start_program()

