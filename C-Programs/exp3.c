/*

This code generates a pyramid-shaped number pattern based on the number of rows entered by the user.

START
1. Input `n` (number of rows) from the user.
   // `n` determines the height of the pyramid.
2. FOR each row `i` from 1 to `n`:
   // This outer loop controls the rows of the pyramid.
   a. Print spaces:
      - FOR `s` from 1 to `n - i`:
        - Print a space " ".
        // This centers the numbers for row `i`.
   b. Print increasing numbers:
      - Initialize `k = i`.
      - FOR `j` from 1 to `i`:
        - Print `k`.
        - Increment `k` by 1.
        // This prints numbers starting from `i` and increasing by 1.
   c. Print decreasing numbers:
      - Initialize `k = 2 * i - 2`.
      - FOR `j` from 1 to `i - 1`:
        - Print `k`.
        - Decrement `k` by 1.
        // This prints numbers decreasing back toward the initial number.
   d. Print a newline to move to the next row.
3. Repeat until all rows are printed.
STOP

*/


#include <stdio.h>

int main() {
    int i, j, k, n, s;
    printf("Enter number of rows:");
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        // Print spaces
        for (s = 1; s <= n - i; s++) {
            printf(" ");
        }
        
        // Print increasing numbers
        k = i;
        for (j = 1; j <= i; j++) {
            printf("%d", k++);
        }
        
        // Print decreasing numbers
        k = 2 * i - 2;
        for (j = 1; j < i; j++) {
            printf("%d", k--);
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
