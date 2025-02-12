clear all
clc
pause(1)

S = input("What is the number of simulations=");
p=input("Prob of success=");
n=input("Number of trials=");

U=rand(n, S);
X=sum(U<p);

U_x = unique(X);
n_X = hist(X, length(U_x)); 
rel_freq=n_X/S;

[U_x; rel_freq]
plot(U_x, rel_freq, 'x');
hold on;
plot(0:n, binopdf(0:n, n, p), 'o');
hold off;

title("Binomial Model");
legend("simulation", "theoretical");