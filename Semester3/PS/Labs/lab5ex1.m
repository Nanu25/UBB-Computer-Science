clc
clear all
pause(1)

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7]
length(X)

alpha = input("alfa = ")

norminv(alpha, 0, 1)

%ignore Ci.
[H, P, Ci, Zval] = ztest(X, 8.5, 5, alpha, -1)    %compute everything

%for the final examn. We change the explanation from fprintf.
if H == 1
    fprintf("We reject. The efficientcy standard is not met.");%and p < alpha
    %and t0(Zval) is in the rejection region(RR).
else 
    fprintf("We accept")
end


%b the right tail test.

%h0 = miu = 5.5
%h1 = miu > 5.5

alpha1 = input("Alfa: ")
tinv(1 - alpha1, length(X) - 1)

[H, P, Ci, Stats] = ttest(X, 5.5, alpha1, 1)

if H == 1
    fprintf("The avrage number of files exceeds 5.5")
else
    fprintf("The avrage number DON'T of files exceeds 5.5")
end


%for b.
% alpha = 0.05
%Q: sigma^2(premium) ?= sigma^2(reg) <=> theta = 1
%theta = sigma^2(premium) / sigma^2(reg)
% H0: theta = 1
% H0 theta != 1;
% two tailed test
%F(n1 - 1, n2 - 1)  n1, n2 lenght of arrays.
%finv = (alpha / 2, n1 - 1, n2 - 1).
