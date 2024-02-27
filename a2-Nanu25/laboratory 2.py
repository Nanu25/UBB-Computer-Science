#Generate n random number between [0, 100]
import random

def generateRandomNumbers(list_size : int) -> list:
    generate_list = []
    for i in range(list_size):
        generate_list.append(random.randint(0, 100))
    return generate_list


#function for the insertion sort

def insertionSort(list_size: int, number_list: list, step: int) -> list:
    sorted_list = number_list
    number_of_steps = 0
    for i in range(list_size):
        j = i - 1
        number = sorted_list[i]
        while j >= 0 and sorted_list[j] > number:
            sorted_list[j + 1] = sorted_list[j]
            j = j - 1

            number_of_steps = number_of_steps + 1
            if number_of_steps % step == 0:
                print(sorted_list)

        sorted_list[j + 1] = number

        number_of_steps = number_of_steps + 1
        if number_of_steps % step == 0:
            print(sorted_list)

    return sorted_list

#functions for the heap sort.

def printHeap(heap_list : list):
    for i in range(1, len(heap_list)):
        print(heap_list[i], end = " ")
    print("")

def HeapAdd(list_size : int, heap_list : list, step : int, levelHeap : int, number_steps : int):
    if(levelHeap > 1):
        father = levelHeap // 2
        if heap_list[father] < heap_list[levelHeap]:
            (heap_list[father], heap_list[levelHeap]) = (heap_list[levelHeap], heap_list[father])

            number_steps = number_steps + 1;
            if number_steps % step == 0:
                printHeap(heap_list)

        HeapAdd(list_size, heap_list, step, father, number_steps)

def HeapExtract(list_size : int, heap_list : list, step : int, levelHeap : int, node : int, number_steps : int):
    if 2 * node <= levelHeap:
        left_son = heap_list[2 * node]
        right_son = -1
        which_son = 2 * node

        # if i have a right son
        if 2 * node + 1 <= levelHeap:
            right_son = heap_list[2 * node + 1]

        # i choose the best son
        if(right_son >= left_son):
            which_son = 2 * node + 1

        if(heap_list[node] < heap_list[which_son]):
            (heap_list[node], heap_list[which_son]) = (heap_list[which_son], heap_list[node])

            number_steps = number_steps + 1
            if number_steps % step == 0:
                printHeap(heap_list)

            HeapExtract(list_size, heap_list, step, levelHeap, which_son, number_steps)


def HeapSort(list_size : int, heap_list : list, step : int, number_steps : int) -> list:
    for i in range(1, list_size + 1):
        # i move the maximum element to the last position
        (heap_list[1], heap_list[list_size - i + 1]) = (heap_list[list_size - i + 1], heap_list[1])

        number_steps = number_steps + 1;
        if number_steps % step == 0:
            printHeap(heap_list)

        # find the maximum from the elements remains.
        HeapExtract(list_size, heap_list, step, list_size - i,  1, number_steps)

    return heap_list

def BuildHeapList(list_size : int, number_list : list, number_steps : int) -> list:
    heap_list = number_list
    for i in range(2, list_size + 1):
        HeapAdd(list_size, heap_list, step, i, number_steps)

    return  heap_list

#main program

print("Press the option do you want to choose ")
print("1 for insertion sort")
print("2 for  heap sort")
which_sort = int(input(">"))

list_size = int(input("Write the number of numbers you want to generate: "))
list_of_numbers = generateRandomNumbers(list_size)

print("There is the list of numbers: ", list_of_numbers)
step = int(input("Write the step you want to see the partially sorted list "))

if which_sort == 1:
    list_of_numbers = insertionSort(list_size, list_of_numbers, step)
    print(list_of_numbers)
else:
    #Index the list from 1.
    list_of_numbers.insert(0, 0)

    number_steps = 0
    heap_list = BuildHeapList(list_size, list_of_numbers, number_steps)
    heap_list = HeapSort(list_size, heap_list, step, number_steps)
    printHeap(heap_list)

exit()