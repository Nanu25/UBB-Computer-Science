clc
clear all
pause(1)

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7]
length(X)

conflvl = input("Confidence level")
a = 1 - conflvl

z1 = norminv(1 - a / 2, 0, 1)
z2 = norminv(a / 2, 0, 1)

mX = mean(X)
fprintf("%f\n", mX - (5 / sqrt(length(X))) * z1)
fprintf("%f", mX - (5 / sqrt(length (X))) * z2)

%subpoint b.
N = length(X)
z1 = tinv(1 - a / 2, N - 1)
z2 = tinv(a / 2, N - 1)
s = std(X)
fprintf("%f\n", mX - (s / sqrt(length(X))) * z1)
fprintf("%f", mX - (s / sqrt(length (X))) * z2)

%c
s = var(X)
z1 = chi2inv(1 - a / 2, N - 1)
z2 = chi2inv(a / 2, N - 1)
fprintf("%f\n", (N - 1) * s / z1)
fprintf("%f", (N - 1) * s / z2)

%d
var1 = sqrt((N - 1) * s / z1)
var2 = sqrt((N - 1) * s / z2)