clc
clear
pause(1);
%We build the vectors/
X = [20 * ones(1, 2), 21, 22 * ones(1, 3), 23 * ones(1, 6), 24 * ones(1, 5), 25 * ones(1, 9), 26, 26, 27, 27]
Y=[75, 75, 75 76, 76, 77, 77, 78 * ones(1, 5), 79 * ones(1, 8), 80  * ones(1, 8), 81, 82]
mean(X)%//mean value
mean(Y)

varX = var(X, 1)%//variation
varY = var(Y, 1)

sqrt(varX)
sqrt(varY)



