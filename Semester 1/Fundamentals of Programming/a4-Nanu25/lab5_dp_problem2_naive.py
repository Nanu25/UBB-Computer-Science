
def Read_numbers() -> list:
    number_list = input("Tell me the numbers")
    number_list = number_list.split()
    int_numbers = []
    for i in number_list:
        int_numbers.append(int(i))

    return int_numbers

def Save_the_solution(int_numbers : list, subset : list) -> list:
    auxiliary = []
    for i in range(1, len(subset)):
        auxiliary.append(int_numbers[subset[i]])

    return auxiliary

def Generate_subset_with_the_sum_i_want(step : int, current_sum : int, int_numbers : list):
    if step < len(int_numbers):
        for i in range(sol[step - 1] + 1, len(int_numbers)):
            sol.append(i)
            current_sum += int_numbers[i]

            if current_sum == sum_want:
                solution.append(Save_the_solution(int_numbers, sol))

            Generate_subset_with_the_sum_i_want(step + 1, current_sum, int_numbers)
            current_sum -= int_numbers[i]
            sol.pop()

#Main

int_numbers = Read_numbers()
list_size = len(int_numbers)
sum_want = int(input("Tell me the sum you want to obtain"))

sol = [-1]
solution = []
Generate_subset_with_the_sum_i_want(1,0, int_numbers)
if len(solution) == 0:
    print("No solution")
else:
    solution[0].sort()
    print(solution[0])