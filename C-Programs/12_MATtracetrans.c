/*

This code performs the following operations on a square matrix: Trace & Transpose.

Transpose means swapping rows and columns.
The trace of a matrix is the sum of its diagonal elements (top-left to bottom-right).

*/

#include<stdio.h>

void main() {
    int a[10][10], t[10][10], n, sum = 0;
    printf("\nEnter the size of matrix: ");
    scanf("%d", &n);
    
    // Input the matrix
    printf("\nEnter the values:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    // Print the original matrix
    printf("\nGiven square matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }

    // Compute the transpose of the matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            t[j][i] = a[i][j];

    // Print the transpose matrix
    printf("\nTranspose Matrix is:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d\t", t[i][j]);
        printf("\n");
    }

    // Calculate the trace of the matrix
    for(int i = 0; i < n; i++)
        sum += a[i][i];

    printf("\nTrace of Matrix is = %d\n", sum);
}
 
/*

OUTPUT
------------------------------------------------
Enter the size of matrix: 3

Enter the values:
1 2 3 4 5 6 7 8 9

Given square matrix:
1	2	3	
4	5	6	
7	8	9	

Transpose Matrix is:
1	4	7	
2	5	8	
3	6	9	

Trace of Matrix is = 15

*/
