// To find perfect numbers within a specified range

/*

A perfect number is a positive integer equal to the sum of its proper divisors (excluding itself). For example, 6.
6 is a perfect number because its divisors 1,2,3 sum to 6.

*/

#include<stdio.h>
int main(){
	int a,b,n;
	printf("Enter starting range:");
	scanf("%d",&a);
	printf("Enter ending range:");
	scanf("%d",&b);
	for(n=a;n<=b;n++)
	{
		int i=1,sum=0;
		while(i<n)
		{
			if(n%i==0)
				sum=sum+i;
			i++;
		}
		if(sum==n)
			printf("%d\t",n);
		}
	printf("\n");
	return 0;
}

/* 

OUTPUT
--------------------------------------
Enter starting range: 1
Enter ending range: 10

6  28

*/
