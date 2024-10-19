#include<stdio.h>
int main(){
    int m, n, p, q, i, j, k;
    int a[10][10], b[10][10], c[10][10];
    printf("Enter number of rows and columns of first matrix:\n");
    scanf("%d%d", &m, &n);
    printf("Enter the elements of first matrix:\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    printf("Matrix 1:\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d\t", a[i][j]);
        }
	printf("\n");
    }
 
    printf("Enter number of rows and columns of second matrix:\n");
    scanf("%d%d", &p, &q);
    if(n != p){
        printf("Multiplication not possible\n");
        return 0;
    }
    printf("Enter the elements of second matrix:\n");
    for(i = 0; i < p; i++){
        for(j = 0; j < q; j++){
            scanf("%d", &b[i][j]);
        }
    }
    printf("Matrix 2:\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d\t", b[i][j]);
        }
	printf("\n");
    }

    for(i = 0; i < m; i++){
        for(j = 0; j < q; j++){
            c[i][j] = 0;
            for(k = 0; k < p; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    printf("Product of the Matrices: \n");
    for(i = 0; i < m; i++){
        for(j = 0; j < q; j++){
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    return 0;
} 



