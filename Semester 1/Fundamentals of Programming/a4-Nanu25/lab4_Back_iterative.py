import random


def generateRandomPoints(number_elements : int) -> list:
    number_list = []
    points_have = {}
    while (number_elements != 0):
        x = random.randint(0, 5)
        y = random.randint(0, 5)

        #do not have the same point
        if (x, y) in points_have:
            pass
        else:
            number_list.append((x, y))
            points_have[x, y] = 1
            number_elements -= 1

    return number_list

def Determinant(x1 : int, y1 : int, x2 : int, y2 : int, x3 : int, y3 : int) -> int:
    return x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3

def isColiniar(x1 : int, y1 : int, x2 : int, y2 : int, x3 : int, y3 : int) -> bool:
    if Determinant(x1, y1, x2, y2, x3, y3) == 0:
        return 1
    return 0


def Check_subset_has_3points_Coliniar(subset : list):
    have3coliniar = 0
    for i in range(0, len(subset)):
        for j in range(i + 1, len(subset)):
            for k in range(j + 1, len(subset)):
                if isColiniar(number_list[subset[i]][0], number_list[subset[i]][1], number_list[subset[j]][0], number_list[subset[j]][1], number_list[subset[k]][0], number_list[subset[k]][1]):
                    have3coliniar = 1

    if have3coliniar == 1:
        print("Here it is a subset: ")
        for i in subset:
            print(number_list[i], end=" ")
        print("")

def Generate_subsets_with_at_least_3coliniar_points_iterative(list_size : int):
    stack = []
    stack.append(([], 0))
    while stack:
        current_subset, step = stack.pop()
        if len(current_subset) >= 3:
            Check_subset_has_3points_Coliniar(current_subset)

        for i in range(step, list_size):
            stack.append((current_subset + [i], i + 1))

#Main

numbers = int(input("Tell the number of points that you want to generate"))
number_list = generateRandomPoints(numbers)
Generate_subsets_with_at_least_3coliniar_points_iterative(len(number_list))