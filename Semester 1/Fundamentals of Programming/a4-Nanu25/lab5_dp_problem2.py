def Read_numbers() -> list:
    number_list = input("Tell me the numbers")
    number_list = number_list.split()
    int_numbers = []
    for i in number_list:
        int_numbers.append(int(i))

    return int_numbers

def Print_the_numbers_from_subset_that_have_target_sum(user_numbers : list, subset : list):
    numbers_from_solution = []
    for i in range(1, len(subset)):
        numbers_from_solution.append(user_numbers[subset[i]])
    print(numbers_from_solution)

def Generate_subset_with_the_target_sum(step : int, current_sum : int, user_numbers : list, solution : list, target_sum : int):
    if step < len(user_numbers):
        for i in range(solution[step - 1] + 1, len(user_numbers)):
            solution.append(i)
            current_sum += user_numbers[i]

            if current_sum == target_sum:
                Print_the_numbers_from_subset_that_have_target_sum(user_numbers, solution)

            Generate_subset_with_the_target_sum(step + 1, current_sum, user_numbers, solution, target_sum)
            current_sum -= user_numbers[i]
            solution.pop()

def Find_a_subarray_of_target_sum(number_list : list, target_sum : int):
    total_sum = 0
    for i in number_list:
        total_sum += i

    assert (total_sum >= target_sum)

    sum_obtained = [-1] * total_sum * 2

    sum_obtained[0] = 0
    last_sum = 0
    for i in number_list:
        j = last_sum
        while j >= 0:
            if sum_obtained[j] != -1 and sum_obtained[j + i] == -1:
                sum_obtained[j + i] = i     #the last element to add to obtain the sum i + j
            j -= 1
        last_sum += i
        print(sum_obtained)


    if sum_obtained[target_sum] == -1:
        print("Immposible to obtain")
    else:
        numbers_for_sum = []
        last_sum = target_sum
        while last_sum != 0:
            numbers_for_sum.append(sum_obtained[last_sum])
            last_sum -= sum_obtained[last_sum]

        numbers_for_sum.sort()
        print(numbers_for_sum)


def Solve_the_problem():
    user_numbers = Read_numbers()
    target_sum = int(input("Tell me the sum you want to obtain"))

    while True:
        print("1. For dynamic programming implementation")
        print("2. For naive implementation")
        print("3. For exit")
        print("Tell me the option")
        option = input(">")

        if (option == '1'):
            Find_a_subarray_of_target_sum(user_numbers, target_sum)
        elif option == '2':
            sol = [-1]
            Generate_subset_with_the_target_sum(1, 0, user_numbers, sol, target_sum)
        else:
            break

#Main
Solve_the_problem()
