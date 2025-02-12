clc
clear all
pause(1)
%Problem 8.

supA = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
supB = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010,  975];

%At the 5% signifiance level, do the pop variances seem to differ?

%h0: sigma1 = sigma2
%h1: sigma1 != sigma 2 - two tailed test
sig = 0.05;
[h, p, ci, stats] = vartest2(supA, supB, sig, 0);

if h == 0
    fprintf("H0 is not rejected. The variance don t differ\n");
else
    fprintf("H0 is rejected. The variance differ\n");
end

q1 = finv(sig / 2, stats.df1, stats.df2);
q2 = finv(sig / 2, stats.df2, stats.df1);

fprintf("Observed value %f\n", stats.fstat);
fprintf('P-value is %f\n', p);
fprintf('Rejection region R is (-inf, %f) U (%f, inf)\n', q1, q2);

fprintf("\n\n")

%part B.
%At the same signifiance level, on avrage,  does SupplierA seem to be more
%reliable

sig = 0.05;
[h, p, ci, stats] = ttest2(supA, supB, sig, 1, 'equal'); %because we have the same signifiance level

if h == 0
    fprintf("H0 is not rejected. Supplier A is NOT more reliable than B\n")
else
    fprintf("H0 is rejected. Supplier A is more reliable than B\n")
   
end

fprintf('P-value of the test statistic is %e.\n', p)
fprintf('Observed value of the test statistic is %1.4f.\n', stats.tstat)

q1 = tinv(1-sig, stats.df);

fprintf('Rejection region R is (%f, +inf)\n', q1)
