#include <stdio.h>
int main() {
    int i, j, rows, k;
    printf("Enter a number to define the rows: ");
    scanf("%d", &rows);
    printf("\n");
    for (i = 1; i <= rows; i++) {
        for (j = i; j < rows; j++) {
            printf(" ");
        }
        for (k = 1; k <= i; k++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}