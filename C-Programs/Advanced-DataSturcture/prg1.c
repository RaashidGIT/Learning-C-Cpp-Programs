#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
int stack[SIZE];
int top = -1;
void push(int x)
{
	if(top == SIZE - 1)
		printf("\nStack overflow occur, Insertion not possible.");
	else
	{
		top = top + 1;
		stack[top] = x;
		printf("\nInsertion successfull");
	}
}
void pop()
{
	if(top == -1)
		printf("\nStack underflow occur, deletion not possible");
	else
	{
		int temp = stack[top];
		top--;		
		printf("\nDeleted element = %d", temp);
	}
}
void display()
{
	int i;
	printf("\nThe elements in the stack are:");
	for(i = top; i >= 0; i--)
		printf("%d  ", stack[i]);
}
void main()
{
	int ch, value;
	while(1)
	{
		printf("\n_____________MENU____________\n");
		printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("\nValue to be inserted is:");
				scanf("%d", &value);
				push(value);
				break;
			case 2: pop();
				break;
			case 3: display();
				break;
			case 4: exit(0);
				break;
			default: printf("\nInvalid choice!");
		}
	}
}
