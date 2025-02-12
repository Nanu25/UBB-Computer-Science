clc
clear all
pause(1)

particles = [3.26 1.89 2.42 2.03 3.07 2.95 1.39 3.06 2.46 3.35 1.56 1.79 1.76 3.82 2.42 2.96];

alpha = 0.05;
%Find 95% conf interval for the avrage size of particles.

meanp = mean(particles);
lenp = length(particles);
rad = sqrt(lenp);
stdp = std(particles);

t = tinv(1 - alpha / 2, lenp - 1);

left = meanp - stdp / rad * t;
right = meanp + stdp / rad * t;

fprintf("The 95 confidence interval is (%.4f, %.4f)\n", left, right);


%At the 1% signifiance level, on avrage, do these nickel particles seem to
%be smaller than 3.

%We need a left tail test.
m0 = 3
alpha = 0.01
[h, p, ci, stats] = ttest(particles, m0, alpha, -1);    %for right tail test we need to put 1.

if h == 0
    fprintf("\nThe null hypothesis is not rejected!\n");
    fprintf("On average the nickel particles are equal to 3!\n");
else 
    fprintf("\nThe null hypothesis is rejected!\n");
    fprintf("On average the nickel particles are smaller than 3!\n");
end


t = tinv(alpha, lenp - 1)

fprintf("The rejection region is (%.4f, %.4f)\n", -inf, t);
fprintf("The test statistics value is: %.4f\n", stats.tstat);
fprintf("The P-value of the test is: %.4f\n", p);
fprintf("The value of H is: %.4f\n", h);


