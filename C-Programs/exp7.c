/*

This program implements the Bubble Sort algorithm to sort an array of integers in ascending order.

START
1. Declare an array `a[10]` and variables `n`, `i`, `j`, `temp`.
2. Input:
   a. Prompt "Enter number of elements (max 10):".
   b. Read `n`.
   c. IF `n <= 0 OR n > 10`:
       - Print "Invalid number of elements."
       - Exit program.
3. Input `n` elements into the array `a`:
   a. Prompt "Enter n elements:".
   b. FOR each index `i` from 0 to n-1:
       - Read `a[i]`.
4. Print the original array:
   a. Loop through `a` and print each element.
5. Bubble Sort:
   a. FOR `i` from 0 to n-2:
      - FOR `j` from 0 to n-i-2:
          i. IF `a[j] > a[j + 1]`:
             - Swap `a[j]` and `a[j + 1]`.
6. Print the sorted array:
   a. Loop through `a` and print each element.
STOP

*/


#include<stdio.h>

int main() {
    int n, i, j, temp, a[10];

    // Input: Number of elements
    printf("Enter number of elements (max 10): ");
    scanf("%d", &n);

    // Validation of input size
    if (n <= 0 || n > 10) {
        printf("Invalid number of elements. Please enter a number between 1 and 10.\n");
        return 1;
    }

    // Input: Array elements
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Display the original array
    printf("\nOriginal array: ");
    for (i = 0; i < n; i++) {
        printf("%d  ", a[i]);
    }

    // Bubble Sort algorithm
    for (i = 0; i < n - 1; i++) {
	// for(j = 0; j < n - 1; j++) Without optimization
        for (j = 0; j < n - i - 1; j++) {  // Optimize: Skip last sorted elements
            if (a[j] > a[j + 1]) {
                // Swap a[j] and a[j + 1]
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    // Display the sorted array
    printf("\nSorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d  ", a[i]);
    }
    printf("\n");

    return 0;
}


/*

OUTPUT
--------------------------------------------
Enter number of elements (max 10): 5
Enter 5 elements: 64 34 25 12 22

Original array: 64  34  25  12  22  
Sorted array: 12  22  25  34  64

*/
