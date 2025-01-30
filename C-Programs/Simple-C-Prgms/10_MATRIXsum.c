/*

The code performs matrix addition of two matrices entered by the user.

*/

#include <stdio.h>

int main() {
    int i, j, rows1, cols1, rows2, cols2;
    int a[10][10], b[10][10], c[10][10];

    // Read first matrix dimensions and elements
    printf("Enter number of rows and columns of first matrix:\n");
    scanf("%d%d", &rows1, &cols1);
    printf("Enter the elements of first matrix:\n");
    for (i = 0; i < rows1; i++)
        for (j = 0; j < cols1; j++)
            scanf("%d", &a[i][j]);

    // Display first matrix
    printf("Matrix 1:\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }

    // Read second matrix dimensions and elements
    printf("Enter number of rows and columns of second matrix:\n");
    scanf("%d%d", &rows2, &cols2);

    // Validate matching dimensions for addition
    if (rows1 != rows2 || cols1 != cols2) {
        printf("Addition not possible\n");
        return 0;
    }

    printf("Enter the elements of second matrix:\n");
    for (i = 0; i < rows2; i++)
        for (j = 0; j < cols2; j++)
            scanf("%d", &b[i][j]);

    // Display second matrix
    printf("Matrix 2:\n");
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }

    // Perform matrix addition
    for (i = 0; i < rows1; i++)
        for (j = 0; j < cols1; j++)
            c[i][j] = a[i][j] + b[i][j];

    // Print result
    printf("Sum of the Matrices:\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }

    return 0;
}

/*

OUTPUT
-------------------------------------------------------------
Enter number of rows and columns of first matrix:
2 3

Enter the elements of first matrix:
1 2 3
4 5 6

Matrix 1:
1   2   3   
4   5   6   

Enter number of rows and columns of second matrix:
2 3

Enter the elements of second matrix:
6 5 4
3 2 1

Matrix 2:
6   5   4   
3   2   1   

Sum of the Matrices:
7   7   7   
7   7   7   


*/


