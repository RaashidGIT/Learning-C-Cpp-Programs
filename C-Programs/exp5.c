/*

This program calculates the factorial of a number using recursion. The factorial of a number n is defined as:
            n! = n × (n−1) × (n−2) × … × 1
For n = 0, by definition, 0! = 1 0! = 1.

START
1. Function `factorial(n)`:
   a. IF `n <= 1`:
       - Return 1. // Base case: Factorial of 0 or 1 is 1.
   b. ELSE:
       - Return `n * factorial(n - 1)`. // Recursive step.
2. In `main()`:
   a. Prompt the user: "Enter a number".
   b. Input `n`.
   c. IF `n < 0`:
       - Print "Factorial is not defined for negative numbers".
   d. ELSE:
       - Call `factorial(n)` and store the result.
       - Print "Factorial of n = result".
STOP

*/

#include<stdio.h>

// Function to calculate factorial using recursion
int factorial(int n) {
    if (n <= 1)  // Base case: 0! = 1 and 1! = 1
        return 1;
    return n * factorial(n - 1);  // Recursive step
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d = %d\n", n, factorial(n));
    }

    return 0;
}

/*

OUTPUT
-----------------------------------
Enter a number: 5
Factorial of 5 = 120

Enter a number: 0
Factorial of 0 = 1

Enter a number: -3
Factorial is not defined for negative numbers.

*/

