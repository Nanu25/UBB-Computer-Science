clc
clear all
pause(1)

%At the 5% signifiance level, do the population variances seem to differ?
standard = [46 37 39 48 47 44 35 31 44 37];
new = [35 33 31 35 34 30 27 32 31 31];

sig = 0.05;

[h, p, ci, stats] = vartest2(standard, new, sig, 0);

if h == 0
    fprintf("H0 is not rejected. The variance don t differ\n");
else
    fprintf("H0 is rejecred. The variance differ")
end


q2 = finv(1-sig/2, stats.df1, stats.df2);
q1 = finv(sig/2, stats.df2, stats.df1);

fprintf('P-value is %1.4f\n', p);
fprintf("the rejection region is (-inf, %f) U (%f, +inf)\n\n", q1, q2)

%part b

% Part b: Confidence interval for the difference in means using standard deviation
mean_standard = mean(standard);
mean_new = mean(new);
std_standard = std(standard);  % Standard deviation of standard group
std_new = std(new);            % Standard deviation of new group
n1 = length(standard);
n2 = length(new);

% Compute pooled variance using standard deviations
pooled_var = (std_standard^2 / n1 + std_new^2 / n2);
df = (pooled_var^2) / (((std_standard^2 / n1)^2 / (n1 - 1)) + ((std_new^2 / n2)^2 / (n2 - 1)));
t_value = tinv(1 - sig / 2, df);

diff_means = mean_standard - mean_new;
margin_of_error = t_value * sqrt(std_standard^2 / n1 + std_new^2 / n2);
lower_bound = diff_means - margin_of_error;
upper_bound = diff_means + margin_of_error;

fprintf("The 95%% confidence interval for the difference of means is (%f, %f)\n", lower_bound, upper_bound);
