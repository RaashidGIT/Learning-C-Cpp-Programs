#include <stdio.h>
int main() {
    int i, j, rows;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    for (i = rows; i >= 1; --i) {
        for (j = 1; j <= rows - i; ++j) {
            printf(" ");
        }
        for (j = 1; j <= i; ++j) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
//This program will take the number of rows as input and then print an inverted right half pyramid pattern using asterisks (*) and spaces.