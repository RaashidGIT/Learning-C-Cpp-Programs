#include <stdio.h>

int main() {
    int i, j, rows1, cols1, rows2, cols2;
    int a[10][10], b[10][10], c[10][10];

    printf("Enter number of rows and columns of first matrix:\n");
    scanf("%d%d", &rows1, &cols1);

    printf("Enter the elements of first matrix:\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Matrix 1:\n");
    for(i = 0; i < rows1; i++){
        for(j = 0; j < cols1; j++){
            printf("%d\t", a[i][j]);
        }
	printf("\n");
    }

    printf("Enter number of rows and columns of second matrix:\n");
    scanf("%d%d", &rows2, &cols2);
    if(rows1 != rows2 || cols1 != cols2){
        printf("Multiplication not possible\n");
        return 0;
    }

    printf("Enter the elements of second matrix:\n");
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    printf("Matrix 2:\n");
    for(i = 0; i < rows2; i++){
        for(j = 0; j < cols2; j++){
            printf("%d\t", b[i][j]);
        }
	printf("\n");
    }

    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("Sum of the Matrices:\n");
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}



