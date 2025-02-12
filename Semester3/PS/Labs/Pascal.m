clear all
clc
pause(1)

S = input("What is the number of simulations=");
p=input("Prob of success=");
n = input("Number of successes=")
X =zeros(1, S);

for i = 1:S
    %%%The i-th simulation
    nofailures = 0;
    nosucc = 0;
    while nosucc ~= n %%while we have a failure
        if rand >= p
            nofailures=nofailures + 1;
        else nosucc = nosucc + 1;
        end
    end
    
    X(i)=nofailures;
end

U_x = unique(X);
n_X = hist(X, length(U_x)); 
rel_freq=n_X/S;

[U_x; rel_freq];
plot(U_x, rel_freq, 'x');
hold on;
plot(0:max(U_x),  nbinpdf(0:max(U_x), n, p), 'o');
hold off;

title("Pascal Model");
legend("simulation", "theoretical");