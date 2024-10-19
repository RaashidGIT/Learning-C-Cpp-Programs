// LINEAR QUEUE

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
int queue[SIZE];
int rear = -1;
int front = -1;
void enqueue(int x)
{
	if(rear == SIZE - 1)
	printf("\nQueue is full, insertion not possible");
	else
	{
		if(front == -1)
			front = 0;
		rear = rear + 1;
		queue[rear] = x;
		printf("\nInsertion successfull.");
	}
}
void dequeue()
{
	if(front == -1 || front > rear)
		printf("\nQueue is empty, deletion not possible");
	else
	{
		printf("\nDeleted element = %d", queue[front]);
		front++;
		if(front > rear)
			front = rear - 1;
	}
}
void display()
{
	int i;
	if(rear == -1)
		printf("\nQueue is empty");
	else
	{
		printf("\nThe elements in queue are: ");
		for(int i = front; i <= rear; i++)
			printf("%d  ", queue[i]);
	}
}
void main()
{
	int ch, value;
	while(1)
	{
		printf("\n__________MENU___________\n");
		printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("\nValue to be inserted is:");
				scanf("%d", &value);
				enqueue(value);
				break;
			case 2: dequeue();
				break;
			case 3: display();
				break;
			case 4: exit(0);
				break;
			default: printf("\nInvalid choice!");
		}
	}
}
