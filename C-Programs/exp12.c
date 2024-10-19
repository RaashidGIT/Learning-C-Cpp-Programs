#include<stdio.h>
void main(){
	int a[10][10],t[10][10], i, j, n, sum;
	printf("\nEnter the size of matrix: ");
	scanf("%d", &n);
	printf("\nEnter the values: ");
	for(i = 0; i < n; i++)
	{	
		for(j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	printf("\n Given square matrix: ");
	for(i = 0; i < n; i++)
	{	
		printf("\n");
		for(j = 0; j < n; j++)
		{
			printf("%d\t", a[i][j]);
		}
	}
	for(i = 0; i < n; i++)
	{	
		for(j = 0; j < n; j++)
		{
			t[j][i] = a[i][j];
		}
	}
	printf("\nTranspose Matrix is: ");
	for(j = 0; j < n; j++)
	{	
		printf("\n");
		for(i = 0; i < n; i++)
		{
			printf("%d\t", t[j][i]);
		}
	}
	sum = 0;
	for(i = 0; i < n; i++)
		sum = sum + a[i][i];
	printf("\nTrace of Matrix is = %d\n", sum);
}
 
	
