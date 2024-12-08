/*

This program implements a stack data structure using a static array in C. 
A stack is a Last In, First Out (LIFO) data structure where the last element inserted is the first to be removed. 
The program supports three main stack operations: Push, Pop, Display.

*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10 
// defines a constant named SIZE with a value of 10

// Global Variables
int stack[SIZE];
int top = -1;

// Function Prototypes
void push(int x);
void pop();
void display();

void main() {
    int ch, value;
    while(1) { // Creates an infinite loop of the MENU
        printf("\n_____________MENU____________\n");
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: 
                printf("\nValue to be inserted: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2: 
                pop();
                break;

            case 3: 
                display();
                break;

            case 4: 
                printf("\nExiting program...\n");
                exit(0);

            default: 
                printf("\nInvalid choice! Please try again.");
        }
    }
}

// Function Definitions

// Insert an element into the stack
void push(int x) {
    if(top == SIZE - 1)
        printf("\nStack Overflow! Insertion not possible.");
    else {
        stack[++top] = x;
        printf("\nInsertion successful.");
    }
}

// Delete an element from the stack
void pop() {
    if(top == -1)
        printf("\nStack Underflow! Deletion not possible.");
    else {
        printf("\nDeleted element = %d", stack[top--]);
    }
}

// Display the stack elements
void display() {
    if(top == -1)
        printf("\nThe stack is empty.");
    else {
        printf("\nThe elements in the stack are: ");
        for(int i = top; i >= 0; i--)
            printf("%d  ", stack[i]);
    }
}

/*

OUTPUT
----------------------------------------------------------
_____________MENU____________

1.Insert
2.Delete
3.Display
4.Exit
Enter your choice: 1

Value to be inserted is: 20
Insertion successful

_____________MENU____________

1.Insert
2.Delete
3.Display
4.Exit
Enter your choice: 3

The elements in the stack are: 20

*/
