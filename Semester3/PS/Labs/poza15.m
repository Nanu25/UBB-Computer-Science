clc
clear all
pause(1)


bank = [3.1 2.9 3.8 3.3 2.7 3.0 2.8 2.5 2.6 2.0 3.2 2.4 2.3 3.1 2.1 3.4]
other = [6.9 6.4 4.7 4.3 5.1 6.3 5.9 5.4 5.3 5.2 5.1 5.9 5.8 4.9]

%At 5% sig level do the population variances seem to differ?

sig = 0.05

[h p ci stats] = vartest2(bank, other, sig, 0);

if h == 0
    fprintf("H0 is not rejected. The variance don t differ\n")
else
    fprintf("H0 is rejected. The variance differ\n")
end


q1 = finv(sig / 2, stats.df1, stats.df2)
q2 = finv(sig / 2, stats.df2, stats.df1)

fprintf("Observed value %f\n", stats.fstat);
fprintf('P-value is %f\n', p);
fprintf('Rejection region R is (-inf, %f) U (%f, inf)\n', q1, q2);

%B At the same sig level, does it seem that, on avrage,, other employees
%dispose of more white paper per year than bank employees.

[h, p, ci, stats] = ttest2(bank, other, sig, 1, 'equal')

if h == 0
    fprintf("H0 is not rejected. Other employees DON T dispose of more white paper per year than bank employees\n")
else
    fprintf("H0 is rejected. The variance differ\n")
end


fprintf('P-value of the test statistic is %e.\n', p)
fprintf('Observed value of the test statistic is %1.4f.\n', stats.tstat)

q1 = tinv(1-sig, stats.df);

fprintf('Rejection region R is (%f, +inf)\n', q1)
