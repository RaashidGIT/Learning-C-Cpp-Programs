/*

This program calculates the sum of elements in an array. 

START
1. Declare an integer array `a[20]`, and variables `n`, `i`, and `sum = 0`.
2. Print "Enter the number of elements (max 20):".
   a. Input `n`.
   b. IF `n <= 0 OR n > 20`:
        - Print "Invalid number of elements."
        - Exit program.
3. Print "Enter n elements:".
   a. FOR each index `i` from 0 to `n - 1`:
        - Input `a[i]`.
4. FOR each index `i` from 0 to `n - 1`:
   a. Add `a[i]` to `sum`.
5. Print "Sum of the elements: sum".
STOP

*/

#include<stdio.h>

int main() {
    int n, i, sum = 0;
    int a[20]; // Array to store up to 20 elements

    printf("Enter the number of elements (max 20): ");
    scanf("%d", &n);

    if (n > 20 || n <= 0) {
        printf("Invalid number of elements. Please enter a number between 1 and 20.\n");
        return 1; // Indicate an error: negative input
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]); // Input each array element
    }

    for (i = 0; i < n; i++) {
        sum += a[i]; // Add each element to the sum
    }

    printf("Sum of the elements: %d\n", sum);
    return 0; // Indicate successful execution
}

/*

OUTPUT
-----------------------------------------
Enter the number of elements (max 20): 4
Enter 4 elements:
10
20
30
40
Sum of the elements: 100

*/
