#include <stdio.h>
int main() {
    int i, j, rows;
    printf("Enter a number to define the rows: ");
    scanf("%d", &rows);
    printf("\n");
    for (i = rows; i > 0; i--) {
        for (j = i; j > 0; j--) {
            printf("* ");
        }
        printf("\n");
    }
    return 0;
}