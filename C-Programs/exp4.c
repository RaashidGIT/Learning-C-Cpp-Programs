#include<stdio.h>
void main()
{
	char pass[10],ch;
	int i,n;
	printf("Enter 8 characters\n");
	for(i = 0; i< 8; i++)
	{
		ch = getchar();
		pass[i] = ch;
		ch = '*';
		printf("%c", ch);
	}
	printf("\n");
}
