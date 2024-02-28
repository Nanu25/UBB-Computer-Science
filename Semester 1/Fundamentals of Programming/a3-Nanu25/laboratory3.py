#Generate n random number between [0, 100]
import random
import timeit

def generateRandomNumbers(list_size : int) -> list:
    generate_list = []
    for i in range(list_size):
        generate_list.append(random.randint(0, 100))
    return generate_list


def createBestCaselist(list_size : int) -> list:
    generate_list = [1]
    for i in range(2, 2 * list_size, 2):
        generate_list.append(i)
    return generate_list

def createWorstCaselist(list_size : int) -> list:
    generate_list = createBestCaselist(list_size)
    generate_list.reverse()
    return generate_list

#function for the insertion sort
'''
    O(n) = n^2
    BC(n) = O(n), when the list is already sorted
    WC(n) = O(n^2), when the list is sorted but in reverse
    AC(n) = O(n^2)
'''
def insertionSort(list_size: int, number_list: list) -> list:
    sorted_list = number_list
    for i in range(list_size):
        j = i - 1
        number = sorted_list[i]
        while j >= 0 and sorted_list[j] > number:
            sorted_list[j + 1] = sorted_list[j]
            j = j - 1

        sorted_list[j + 1] = number
    return sorted_list

#functions for the heap sort.

'''
    O(n) = nlog2(n)
    BC(n) = nlog2(n)
    WC(n) = nlog2(n)
    AC(n) = nlog2(n)
'''

def printHeap(heap_list : list):
    for i in range(1, len(heap_list)):
        print(heap_list[i], end = " ")
    print("")

def HeapAdd(list_size : int, heap_list : int, levelHeap : int):
    if(levelHeap > 1):
        father = levelHeap // 2
        if heap_list[father] < heap_list[levelHeap]:
            (heap_list[father], heap_list[levelHeap]) = (heap_list[levelHeap], heap_list[father])

        HeapAdd(list_size, heap_list, father)

def HeapExtract(list_size : int, heap_list : list, levelHeap : int, node : int):
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
            HeapExtract(list_size, heap_list, levelHeap, which_son)


def HeapSort(list_size : int, heap_list : list) -> list:
    # Index the list from 1.
    heap_list.insert(0, 0)

    heap_list = BuildHeapList(list_size, heap_list)
    for i in range(1, list_size + 1):
        # i move the maximum element to the last position
        (heap_list[1], heap_list[list_size - i + 1]) = (heap_list[list_size - i + 1], heap_list[1])

        # find the maximum from the elements remains.
        HeapExtract(list_size, heap_list, list_size - i,  1)

    return heap_list

def BuildHeapList(list_size : int, number_list : list) -> list:
    heap_list = number_list
    for i in range(2, list_size + 1):
        HeapAdd(list_size, heap_list, i)

    return  heap_list

def Test_insertionSort(list_size : int, option : int):
    for i in range (5):
        if option == 1:
            list_of_numbers = createWorstCaselist(list_size)
        elif option == 2:
            list_of_numbers = generateRandomNumbers(list_size)
        else:
            list_of_numbers = createBestCaselist(list_size)

        start_time = timeit.default_timer()
        list_of_numbers = insertionSort(list_size, list_of_numbers)

        print("The lenght of the list was ", list_size, "and the time took by the program was ", timeit.default_timer() - start_time)


        list_size = list_size * 2


def Test_heapSort(list_size : int, option : int):
    for i in range(5):
        if option == 1:
            list_of_numbers = createWorstCaselist(list_size)
        elif option == 2:
            list_of_numbers = generateRandomNumbers(list_size)
        else:
            list_of_numbers = createBestCaselist(list_size)

        start_time = timeit.default_timer()
        heap_list = HeapSort(list_size, list_of_numbers)

        print("The lenght of the list was ", list_size, "and the time took by the program was ", timeit.default_timer() - start_time)
        list_size = list_size * 2

#main program

print("Press the option do you want to choose ")
print("1 for worst case for both insertion sort and heap sort")
print("2 for avrage case for both insertion sort and heap sort")
print("3 for best case for both insertion sort and heap sort")
print("4 for worst case for insertion sort")
print("5 for avrage case for insertion sort")
print("6 for best case for insertion sort")
print("7 for worst case for heap sort")
print("8 for avrage case for heap sort")
print("9 for best case for heap sort")
which_case = int(input(">"))

print("")
list_size = int(input("Write the number of numbers you want to generate: "))
list_of_numbers = []

if which_case == 1:
    #exemple n = 1000
    print("Times for insertion sort ")
    Test_insertionSort(list_size,1)

    print(" ")

    print("Times for heap sort ")
    Test_heapSort(list_size, 1)

elif which_case == 2:

    # exemple n = 1000
    print("Times for insertion sort ")
    Test_insertionSort(list_size, 2)


    print(" ")
    print("Times for heap sort ")
    Test_heapSort(list_size, 2)

elif which_case == 3:
    # exemple n = 1000
    print("Times for insertion sort ")
    Test_insertionSort(list_size,3)

    print(" ")
    print("Times for heap sort ")
    Test_heapSort(list_size, 3)
elif which_case == 4:
    print("Times for insertion sort ")
    Test_insertionSort(list_size, 1)
elif which_case == 5:
    print("Times for insertion sort ")
    Test_insertionSort(list_size, 2)
elif which_case == 6:
    print("Times for insertion sort ")
    Test_insertionSort(list_size, 3)
elif which_case == 7:
    print("Times for heap sort ")
    Test_heapSort(list_size, 1)
elif which_case == 8:
    print("Times for heap sort ")
    Test_heapSort(list_size, 2)
else:
    print("Times for heap sort ")
    Test_heapSort(list_size, 3)

exit()