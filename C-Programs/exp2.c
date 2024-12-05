/*

This C program checks if a given positive integer n is a prime number or not.

A prime number is greater than 1 and divisible only by 1 and itself.
For example: 
2,3,5,7 are prime numbers.
4,6,8,9 are not prime numbers because they have divisors other than 1 and themselves.

*/

/*

START
1. Input a positive integer `n` from the user.
   // The number `n` will be checked to determine if it is prime or not.
2. Initialize a variable `flag` to 0.
   // `flag` is used as a marker to indicate whether `n` has a divisor other than 1 and itself.
   // If `flag` remains 0, `n` is prime. If `flag` becomes 1, `n` is not prime.
3. IF `n` is less than or equal to 1:
   - Print "Not a prime number".
   // Prime numbers must be greater than 1.
4. ELSE:
   - FOR each integer `i` from 2 to `n/2`:
     // Test divisors only up to `n/2`, as a larger divisor would imply a smaller one exists.
     a. IF `n % i == 0`:
        - Set `flag = 1`.
        - BREAK out of the loop.
        // This means `i` is a divisor of `n`, so `n` is not a prime number.
   - IF `flag == 0`:
     - Print "`n` is a prime number".
     // No divisors were found; `n` is prime.
   - ELSE:
     - Print "`n` is not a prime number".
     // A divisor was found; `n` is not prime.
5. END
STOP

*/

#include<stdio.h>
int main() {
    int n, i, flag = 0;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("Not a prime number\n");
        return 0; // Exit early since numbers <= 1 are not prime
    }

    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            flag = 1; // Mark as not prime
            break;    // Exit loop early as we found a divisor
        }
    }

    if (flag == 0)
        printf("%d is a prime number\n", n);
    else
        printf("%d is not a prime number\n", n);

    return 0;
}

/*

OUTPUT
-------------------
Enter a positive integer: 7
7 is a prime number.

*/	
