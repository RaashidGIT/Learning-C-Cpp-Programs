/*

This program performs matrix multiplication between two matrices A (m x n) and B (p x q).


*/

#include<stdio.h>

int main() {
    int m, n, p, q, i, j, k;
    int a[10][10], b[10][10], c[10][10] = {0}; // Initialize result matrix with zeros

    // Input first matrix
    printf("Enter rows and columns of first matrix: ");
    scanf("%d%d", &m, &n);
    printf("Enter elements of first matrix:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    // Display first matrix
    printf("Matrix 1:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }

    // Input second matrix
    printf("Enter rows and columns of second matrix: ");
    scanf("%d%d", &p, &q);

    // Check if multiplication is possible
    if (n != p) {
        printf("Multiplication not possible\n");
        return 0;
    }

    printf("Enter elements of second matrix:\n");
    for (i = 0; i < p; i++)
        for (j = 0; j < q; j++)
            scanf("%d", &b[i][j]);

    // Display second matrix
    printf("Matrix 2:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < q; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }

    // Perform matrix multiplication
    for (i = 0; i < m; i++) {
        for (j = 0; j < q; j++) {
            for (k = 0; k < n; k++) {  // Correct multiplication size condition
                c[i][j] += a[i][k] * b[k][j];  // Sum product of corresponding elements
            }
        }
    }

    // Display result matrix
    printf("Product of the matrices:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < q; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }

    return 0;
}

/*

OUTPUT
------------------------------------------------------------------
Enter rows and columns of first matrix: 2 3
Enter elements of first matrix: 
1 2 3 4 5 6

Enter rows and columns of second matrix: 3 2
Enter elements of second matrix: 
7 8 9 10 11 12

Matrix 1:
1   2   3   
4   5   6   

Matrix 2:
7   8   
9  10   
11 12   

Product of the matrices:
58  64   
139 154   

*/



