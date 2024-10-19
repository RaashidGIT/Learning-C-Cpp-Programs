// CIRCULAR QUEUE

#include<stdio.h>
#define MAX 5
int enqueue[MAX];
int front = -1;
int rear = -1;
void insert(int item)
{
	if((front == 0 && rear == MAX - 1) || (front == rear + 1))
	{
		printf("Queue overflow\n");
		return;
	}
	if(front == -1)
	{
		front = 0;
		rear = 0;
	}
	else
	{
		if(rear == MAX - 1)
			rear = 0;
		else
			rear = rear + 1;
	}
	enqueue[rear] = item;
}
void del()
{
	if(front == -1)
	{
		printf("\nQueue underflow\n");
		return;
	}
	printf("\nThe element deleted from queue is : %d\n", enqueue[front]);
	if(front == rear)
	{
		front = -1;
		rear = -1;
	}
	else
	{
		if(front == MAX - 1)
			front = 0;
		else
			front = front + 1;
	}
}
void display()
{
	int front_pos = front, rear_pos = rear;
	if(front == -1)
	{
		printf("\nQueue is empty\n");
		return;
	}
	printf("\nThe elements in queue are: ");
	if(front_pos <= rear_pos)
		while(front_pos <= rear_pos)
		{
			printf("%d  ", enqueue[front_pos]);
			front_pos++;
		}
	else
	{
		while(front_pos <= MAX - 1)
		{
			printf("%d  ", enqueue[front_pos]);
			front_pos++;
		}
		front_pos = 0;
		while(front_pos <= rear_pos)
		{
			printf("%d  ", enqueue[front_pos]);
			front_pos++;
		}
	}
	printf("\n");
}
int main()
{
	int ch, value;
	do
	{
		printf("\n");
		printf("\n__________MENU___________\n");
		printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("\nValue to be inserted is:");
				scanf("%d", &value);
				insert(value);
				break;
			case 2: del();
				break;
			case 3: display();
				break;
			case 4: break;
			default: printf("\nInvalid choice!");
		}
	}
	while(ch!= 4);
	return 0;
}
	
