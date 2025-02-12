clc
clear all
pause(1)


%At 5% signifiance level do the population variances seem to differ?
steel = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4];
glass = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4];

sig = 0.05;
[h, p, ci, stats] = vartest2(steel, glass, sig, 0);

if h == 0
    fprintf("H0 is not rejected. The variance don t differ\n");
else
     fprintf("H0 is rejected. The variances differ\n");
end

q2 = finv(1-sig/2, stats.df1, stats.df2);
q1 = finv(sig/2, stats.df2, stats.df1);

fprintf('P-value is %1.4f\n', p);
fprintf("the rejection region is (-inf, %f) U (%f, +inf)", q1, q2)


%part B.
%At the same signifiance level, does it seem that on avrage, steel pipes
%lose more heat than glass?

[h, p, ci, stats] = ttest2(steel, glass, sig, 1, 'equal');

if h == 0
      fprintf('H0 is not rejected. Steel pipes do NOT lose more heat than glass.\n')
else
      fprintf('H0 is rejected. Steel pipes do lose more heat than glass pipes.\n')
end

fprintf('P-value of the test statistic is %e.\n', p)

q1 = tinv(1 - sig, stats.df);

fprintf('Rejection region R is (%3.4f, +inf)\n', q1)