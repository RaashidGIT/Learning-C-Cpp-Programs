#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
} *front = NULL, *rear = NULL;

void enqueue(){
	struct node *newnode = (struct node*) malloc (sizeof(struct node));
	printf("\nEnter the data to be inserted: ");
	scanf("%d", &newnode -> data);
	newnode -> next = NULL;
	if(front == NULL && rear == NULL)
		front = rear = newnode;
	else{
		rear -> next = newnode;
		rear = newnode;
	}
}

void dequeue(){
	if(front == NULL && rear == NULL)
		printf("\n Empty queue");
	else
	{
		struct node *temp = front;
		front = front -> next;
		if(front == NULL)
			rear = NULL;
		printf("\nDeleted node:%d", temp -> data);
		free(temp);
	}
}

void display(){
	if (front == NULL && rear == NULL)
		printf("Empty queue");
	else{
		struct node *temp = front;
		printf("\nThe queue:");
		while(temp!= NULL){
			printf("%d --->", temp -> data);
			temp = temp -> next;
		}
		printf("NULL");
	}
}

void main(){
	int ch;
	while(1){
		printf("\n____________________QUEUE USING LINKED LIST____________________");
		printf("\n___MENU___\n1/Insert\n2/Delete\n3/Display\n4/Exit\n");
		printf("\nEnter choice");
		scanf("%d", &ch);
		switch(ch){
			case 1: enqueue();
				break;
			case 2: dequeue();
				break;
			case 3: display();
				break;
			case 4: exit(0);
				break;
			default: printf("Invalid choice");
		}
	}
}	
