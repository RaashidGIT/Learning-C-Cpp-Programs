/*

This code generates a pyramid-shaped number pattern based on the number of rows entered by the user.

START
1. Input `n` (number of rows) from the user.
   // `n` determines the height of the pyramid.
2. FOR each row `i` from 1 to `n`:
   // The outer loop controls the number of rows.
   a. Print spaces:
      - FOR `j` from 1 to `n - i`:
        - Print a space " ".
        // Print enough spaces to center-align the numbers in row `i`.
   b. Print increasing numbers:
      - FOR `j` from 0 to `i - 1`:
        - Print `i + j`.
        // Start at `i` and increment the number with each iteration.
   c. Print decreasing numbers:
      - FOR `j` from `i - 2` down to 0:
        - Print `i + j`.
        // Start where the increasing numbers left off and decrement back.
   d. Print a newline:
      - Move to the next row.
3. Repeat until all rows are printed.
STOP


*/


#include <stdio.h>

int main() {
    int i, j, n;
    printf("Enter number of rows: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        // Print spaces
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // Print increasing numbers
        for (j = 0; j < i; j++) {
            printf("%d", i + j);
        }

        // Print decreasing numbers
        for (j = i - 2; j >= 0; j--) {
            printf("%d", i + j);
        }

        printf("\n");
    }

    return 0;
}

/*

OUTPUT
-----------------------------------------
Enter number of rows: 4
   1
  232
 34543
4567654

*/
