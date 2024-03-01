
def original_sum(n : int) -> float:
    sum = 0
    for i in range(1, n + 1):
        if i % 2 == 0:
            sum += -1 / i
        else:
            sum += 1 / i
    return sum

def modified_sum(n : int, p : int, q : int) -> float:
    sum = 0
    okp = 1
    cntp = 0
    cntq = 0
    for i in range(1, n + 1):
        if okp == 1:
            sum += 1 / i
            cntp += 1
            if cntp % p == 0:
                okp = 0
        else:
            sum += -1 / i
            cntq += 1
            if cntq % q == 0:
                okp = 1
    return sum


n = int(input("Tell me the number of elements in the series"))
p = int(input("Tell me the number p = "))
q = int(input("Tell me the number q = "))
print("The original sum is ", original_sum(n))
print("The modified sum is ", modified_sum(n, p, q))

