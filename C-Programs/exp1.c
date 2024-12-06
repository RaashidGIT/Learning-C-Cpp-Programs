// To find perfect numbers within a specified range

/*

A perfect number is a positive integer equal to the sum of its proper divisors (excluding itself). 
For example, 6.
6 is a perfect number because its divisors 1,2,3 sum to 6.

START
1. Declare variables `start`, `end`, `num`, `i`, `sum`.
2. Prompt the user:
   - "Enter starting range:"
   - Input `start`.
3. Prompt the user:
   - "Enter ending range:"
   - Input `end`.
4. Print "Perfect numbers in the range start to end are:"
5. FOR each number `num` from `start` to `end` (inclusive):
   a. Set `sum = 0`.
   b. FOR each potential divisor `i` from 1 to `num / 2`:
      - IF `num % i == 0`: // `i` is a divisor of `num`
         - Add `i` to `sum`.
   c. IF `sum == num`: // Check if the number is perfect
      - Print `num`.
6. Print a newline for formatting.
STOP


*/

#include <stdio.h>

int main() {
    int start, end, num, i, sum;

    // Input starting and ending range
    printf("Enter starting range: ");
    scanf("%d", &start);
    printf("Enter ending range: ");
    scanf("%d", &end);

    printf("Perfect numbers in the range %d to %d are:\n", start, end);

    // Iterate through the range
    for (num = start; num <= end; num++) {
        sum = 0;

        // Find divisors of num and calculate their sum
        for (i = 1; i <= num / 2; i++) {
            if (num % i == 0)
                sum += i;
        }

        // Check if the number is perfect
        if (sum == num)
            printf("%d ", num);
    }

    printf("\n");
    return 0;
}


/* 

OUTPUT
--------------------------------------
Enter starting range: 1
Enter ending range: 100

6  28

*/
