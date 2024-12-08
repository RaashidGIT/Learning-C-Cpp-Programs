/*

This code implements a queue using a linked list in C.

*/

#include<stdio.h>
#include<stdlib.h>

// Function declarations
void ENQUEUE();  // Insert element into the queue
void DEQUEUE();  // Remove element from the queue
void DISPLAY();  // Display all elements in the queue

// Definition of a linked list node
struct node {
    int data;          // Data part of the node
    struct node *next; // Pointer to the next node
};

// Pointers to track the front and rear of the queue
struct node *front = NULL;
struct node *rear = NULL;

void main() {
    int choice;
    printf("\nQUEUE OPERATIONS USING LINKED LIST\n");

    // Infinite loop for menu-driven interaction
    while (1) {
        // Display menu options
        printf("\n INSERT \nDELETE \nDISPLAY\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);

        // Menu-driven switch-case
        switch (choice) {
            case 1:
                ENQUEUE();  // Insert element
                break;
            case 2:
                DEQUEUE();  // Remove element
                break;
            case 3:
                DISPLAY();  // Display elements
                break;
            case 4:
                exit(0);   // Exit program
            default:
                printf("Enter a valid choice:\n");  // Handle invalid inputs
        }
    }
}

void ENQUEUE() {
    struct node *newnode;    // Create a new node
    int item;
    newnode = (struct node*)malloc(sizeof(struct node));  // Allocate memory
    
    printf("Enter the data: ");
    scanf("%d", &newnode->data);  // Store input data in the new node

    if (front == NULL) {  // If the queue is empty
        front = newnode;  // New node becomes both front and rear
        rear = newnode;
        front->next = NULL;  // Set next pointers to NULL
        rear->next = NULL;
    } else {
        rear->next = newnode;  // Link new node to the rear of the queue
        rear = newnode;        // Update rear pointer
        rear->next = NULL;     // Ensure rear's next is NULL
    }
}

void DEQUEUE() {
    struct node *ptr;  // Temporary pointer for deletion

    if (front == NULL) {  // Check if the queue is empty
        printf("\nUNDERFLOW\n");  // Queue underflow message
    } else {
        ptr = front;  // Store the current front
        printf("%d deleted\n", ptr->data);  // Print deleted element
        front = front->next;  // Update front to the next node
        free(ptr);  // Free memory of the deleted node
    }
}

void DISPLAY() {
    struct node *temp;  // Temporary pointer for traversal
    temp = front;       // Start from the front of the queue

    if (front == NULL) {  // If the queue is empty
        printf("Queue is empty\n");
        return;
    }

    // Traverse and print all elements
    while (temp != NULL) {
        printf("%d\t", temp->data);  // Print current element
        temp = temp->next;           // Move to the next element
    }
    printf("\n");  // Newline after printing all elements
}

/*

OUTPUT
-----------------------------------------------------------------------------
QUEUE OPERATIONS USING LINKED LIST

 INSERT 
DELETE 
DISPLAY
Enter a choice: 1
Enter the data: 10

 INSERT 
DELETE 
DISPLAY
Enter a choice: 1
Enter the data: 20

 INSERT 
DELETE 
DISPLAY
Enter a choice: 3
10	20	

 INSERT 
DELETE 
DISPLAY
Enter a choice: 2
10 deleted

 INSERT 
DELETE 
DISPLAY
Enter a choice: 3
20

*/
