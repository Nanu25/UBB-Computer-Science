clear all
clc
pause(1)

S = input("What is the number of simulations=");
p=input("Prob of success=");


U=rand(1, S);
X=U<p;

U_x = unique(X);
n_X = hist(X, length(U_x));
rel_freq=n_X/S;

[U_x; rel_freq]