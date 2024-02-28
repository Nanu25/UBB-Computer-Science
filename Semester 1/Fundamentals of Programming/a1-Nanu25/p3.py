# Solve the problem from the third set here #13
n = int(input())
x = 1
while n != 0 :
    cop = x
    d = 2

    if x == 1 and n == 1:
        print(1)
        break
    elif x == 1:
        n = n - 1

    while cop > 1:
        exp = 0
        while cop % d == 0:
            cop = cop / d
            exp = exp + 1

        if exp != 0 and n > 0:
            n = n - 1

        if n == 0:
            break

        d = d + 1
        if d * d > cop:
            d = cop

    if n == 0:
        print(int(d))

    x = x + 1
