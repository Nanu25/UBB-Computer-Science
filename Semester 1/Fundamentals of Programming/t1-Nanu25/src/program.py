ADD_A_PRODUCT = "add"
REMOVE_A_PRODUCT = "remove"
LIST_ITEM_IN_DEACREASING_ORDER = "listall"
#
# Functions section
#

def Add_a_product(product_name : str, quantity : int, item_price : int) -> tuple:
    """ 

    :param product_name: the name for the new item
    :param quantity: the number of new items that we add
    :param item_price: price for each item
    :return: a tuple with this 3 parameters
    """

    if quantity < 0 or item_price < 0:
        raise ValueError("Invalid input")

    return [product_name, quantity, item_price]

def remove_a_product_by_its_name(ware_house : tuple, name_of_product : str) -> tuple:
    """

    :param ware_house: the list of item that i have
    :param name_of_product: name of the product that i want to delete
    :return: the ware house list without the item from the input
    """
    new_ware_house = []
    find_the_item = False
    for item in ware_house:
        if item[0] == name_of_product:
            find_the_item = True
            continue
        new_ware_house.append(item)

    if find_the_item == False:
        raise ValueError("This item doesn't exist")

    return new_ware_house

def print_sorted_ware_house_items_deacreasing(ware_house : tuple) -> tuple:
    for i in range(0, len(ware_house)):
        for j in range(i, len(ware_house)):
            if(ware_house[i][0] < ware_house[j][0]):
                ware_house[i], ware_house[j] = ware_house[j], ware_house[i]

    print(ware_house)

def make_the_total_sum_of_list(ware_house : tuple) -> int:
    total_sum = 0
    for item in ware_house:
        total_sum += item[1] * item[2]

    return total_sum

#
# User interface section
#

def Start_program():
    ware_house = []
    while True:
        s = input()
        s = s.split()

        if s[0] == ADD_A_PRODUCT:
            if len(s) < 4:
                print("Invalid input")
                continue
            try:
                quantity = int(s[2])
                item_price = int(s[3])
                ware_house.append(Add_a_product(s[1], quantity, item_price))
            except ValueError as ve:
                print(ve)
        elif s[0] == REMOVE_A_PRODUCT:
            try:
                ware_house = remove_a_product_by_its_name(ware_house, s[1])
            except ValueError as ve:
                print(ve)

        elif s[0] + s[1] == LIST_ITEM_IN_DEACREASING_ORDER:
            print_sorted_ware_house_items_deacreasing(ware_house)
        else:
            print(make_the_total_sum_of_list(ware_house))

Start_program()