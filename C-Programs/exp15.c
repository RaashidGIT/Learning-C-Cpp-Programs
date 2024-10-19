#include <stdio.h>
#include <math.h>

int main() {
    int s, n, r, d = 0, digits = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    s = n;

    // Counting digits
    while (n != 0) {
        n /= 10;
        digits++;
    }

    // Reset n to the original value
    n = s; 

    // Armstrong number check
    while (n != 0) {
        r = n % 10;
        d = d + pow((double)r, (double)digits);
        n = n / 10;
    }

    // Output result
    if (d == s)
        printf("\n%d is an Armstrong number\n", s);
    else
        printf("\n%d is not an Armstrong number\n", s);

    return 0;
}
// gcc exp15.c -lm 

