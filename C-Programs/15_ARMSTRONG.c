/*

This program checks whether a number is an Armstrong number.

An Armstrong number is a number that equals the sum of its digits raised to the power of the number of digits.
153 => (1^3) + (5^3) + (3^3) = 153 (Armstrong Number)
9474 => (9^4) + (4^4) + (7^4) + (4^4) = 9474 (Armstrong Number)

*/

#include <stdio.h>
#include <math.h>

int main() {
    int s, n, r, d = 0, digits = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    s = n;

    // Counting digits
    while (n != 0) {
        n /= 10; // Remove the last digit
        digits++;
    }

    // Reset n to the original value
    n = s; 

    // Armstrong number check
    while (n != 0) {
        r = n % 10; // Extract the last digit
        d = d + pow((double)r, (double)digits); // Add the digit raised to the power of the number of digits
        n = n / 10; // Remove the last digit
    }

    // Output result
    if (d == s)
        printf("\n%d is an Armstrong number\n", s);
    else
        printf("\n%d is not an Armstrong number\n", s);

    return 0;
}
// gcc exp15.c -lm (Requires due to Math header file)

/*

OUTPUT
-------------------------------------------------------------
Enter a number: 153

153 is an Armstrong number

*/
