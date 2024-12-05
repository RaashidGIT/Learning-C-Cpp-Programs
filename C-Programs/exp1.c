// To find perfect numbers within a specified range

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
