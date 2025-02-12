clc
clear all
pause(1)

X = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0]
Y = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2]


conflvl = input("Confidence level")
a = 1 - conflvl


n1 = length(X)
n2 = length(Y)

s1 = var(X)
s2 = var(Y)
sp = sqrt(((n1 - 1) * s1 + (n2 - 1) * s2) / (n1 + n2 - 2))
mX = mean(X)
mY = mean(Y)
z1 = tinv(1 - a / 2, n1 + n2 - 2)
z2 = tinv(1 - a / 2, n1 + n2 - 2)
fprintf("%f \n" , mX - mY - z1- sp * sqrt(1/n1 + 1/n2))
fprintf("%f \n", mX - mY + z2 - sp*sqrt(1/n1 + 1/n2))