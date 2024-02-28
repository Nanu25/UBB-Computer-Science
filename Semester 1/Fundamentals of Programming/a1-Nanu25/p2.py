# Solve the problem from the second set here
a = int(input())
b = int(input())
P = 1
for i in range(10):
    copa = a
    copb = b
    oka = 0
    okb = 0
    while copa != 0:
        if copa % 10 == i:
            oka = 1
        copa = int(copa / 10)

    while copb != 0:
        if copb % 10 == i:
            okb = 1
        copb = copb // 10

    if oka == 0 and okb == 1:
         P = 0

    if oka == 1 and okb == 0:
        P = 0

if P == 1:
    print("DA")
else:
    print("NU")

