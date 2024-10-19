#include<stdio.h>
int main(){
	int n, i, sum = 0, a[20];
	printf("Enter the number of elements:\n");
	scanf("%d", &n);
	printf("Enter %d elements into array:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < n; i++)
	{
		sum += a[i];
	}
	printf("Sum is: %d\n", sum);
	return 0;
} 

