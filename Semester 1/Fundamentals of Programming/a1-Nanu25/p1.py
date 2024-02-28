import math

def is_prime(n):
    if n < 2:
        return 0
    for d in range(2, int(math.sqrt(n)) + 1):
        if n % d == 0:
            return 0
    return 1

n = int(input())
for i in range(2, n):
    if is_prime(i) == 1 and is_prime(n - i):
        print(i, n - i)
        break
