#include <stdio.h>

int number_of_prime_factor_apparence(int n, int p) {
    /*
     * Return the exponent of p that appears in the number n.
     * n - number
     * p - prime factor
     */

    int exponent = 0;
    while(n % p == 0) {
        exponent++;
        n /= p;
    }

    return exponent;
}

int gcd(int a, int b) {
    /*
     * a - the first number
     * b - the second number
     * return the gcd of a and b.
     */
    while(b) {
        int rest = a % b;
        a = b;
        b = rest;
    }
    return a;
}

int main() {
    int cer;
    printf("Tell 1 for first task or 2 for the second task: ");
    scanf("%d", &cer);
    if(cer == 1) {
        int n, p;
        printf("Tell the number n=");
        scanf("%d", &n);
        printf("Tell the number p=");
        scanf("%d", &p);
        printf("%d", number_of_prime_factor_apparence(n, p));
    } else {
        int n;
        printf("\nTell the length of the vector n=");
        scanf("%d", &n);
        int v[n];
        printf("\nWrite the elements");
        for(int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
        }

        int lg = 1, lgmax = 1, left = 0, right = 0;
        for(int i = 1; i < n; i++) {
            if(gcd(v[i - 1], v[i]) == 1)
                lg++;
            else lg = 1;

            if(lg > lgmax) {
                left = i - lg + 1;
                right = i;
                lgmax = lg;
            }
        }

        for(int i = left; i <= right; i++)
            printf("%d ", v[i]);

    }
    return 0;
}
