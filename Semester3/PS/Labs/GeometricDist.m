clear all
clc
pause(1)

S = input("What is the number of simulations=");
p=input("Prob of success=");

X =zeros(1, S);

for i = 1:S
    %%%The i-th simulation
    nofailures = 0;
    while rand>= p %%while we have a failure
        nofailures=nofailures + 1;
    end
    
    X(i)=nofailures;
end

U_x = unique(X);
n_X = hist(X, length(U_x)); 
rel_freq=n_X/S;

[U_x; rel_freq]
plot(U_x, rel_freq, 'x');
hold on;
plot(0:max(U_x),  geopdf(0:max(U_x), p), 'o');
hold off;

title("Geometrical Model");
legend("simulation", "theoretical");