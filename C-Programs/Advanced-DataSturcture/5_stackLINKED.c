/*

This code implements a stack using a linked list in C.

*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct node {
    int data;           // Data to be stored in the node
    struct node *next;  // Pointer to the next node
} *top = NULL;

// Function prototypes
void push(int);    // Function to insert a new element into the stack
void pop(void);    // Function to remove the top element from the stack
void display(void); // Function to display all elements in the stack

int main() {
    int choice, value;

    printf("******* STACK USING LINKED LIST *******\n");

    // Infinite loop for menu-driven program
    while (1) {
        printf("\nMenu:\n");
        printf("1. PUSH (Insert)\n");
        printf("2. POP (Delete)\n");
        printf("3. DISPLAY (Show Stack)\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform operations based on user choice
        switch (choice) {
            case 1: // Insert element into the stack
                printf("Enter the value to be inserted: ");
                scanf("%d", &value);
                push(value); 
                break;

            case 2: // Remove element from the stack
                pop(); 
                break;

            case 3: // Display all elements in the stack
                display(); 
                break;

            case 4: // Exit the program
                exit(0);

            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0; 
}

// Function to insert an element into the stack
void push(int val) {
    // Allocate memory for the new node
    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    // Check if memory allocation failed
    if (newnode == NULL) {
        printf("Memory allocation failed! Stack overflow.\n");
        return;
    }

    // Assign data and adjust pointers
    newnode->data = val; 
    newnode->next = top;  // Link the new node to the current top
    top = newnode;        // Update top to the new node

    printf("Insertion successful!\n");
}

// Function to remove the top element from the stack
void pop() {
    if (top == NULL) {  // Check if the stack is empty
        printf("Stack is empty! No elements to delete.\n");
    } else {
        struct node *temp = top; // Store the top element temporarily
        printf("%d is deleted.\n", temp->data); // Display the deleted value
        top = temp->next; // Update top to the next element
        free(temp); // Free memory of the deleted node
    }
}

// Function to display all elements in the stack
void display() {
    if (top == NULL) {  // Check if the stack is empty
        printf("Stack is empty!\n");
    } else {
        struct node *temp = top;  // Start from the top element
        printf("Stack contents: ");
        while (temp != NULL) {  // Traverse through the stack
            printf("%d --> ", temp->data);  // Print current element
            temp = temp->next;  // Move to the next element
        }
        printf("NULL\n");  // End of the stack display
    }
}

/*

OUTPUT
----------------------------------------------------------------
******* STACK USING LINKED LIST *******

Menu:
1. PUSH (Insert)
2. POP (Delete)
3. DISPLAY (Show Stack)
4. EXIT
Enter your choice: 1
Enter the value to be inserted: 10
Insertion successful!

Menu:
Enter your choice: 1
Enter the value to be inserted: 20
Insertion successful!

Menu:
Enter your choice: 3
Stack contents: 20 --> 10 --> NULL

Menu:
Enter your choice: 2
20 is deleted.

Menu:
Enter your choice: 3
Stack contents: 10 --> NULL

Menu:
Enter your choice: 4

*/
