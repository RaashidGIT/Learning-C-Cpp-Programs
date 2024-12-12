#include <stdio.h>
#include <stdlib.h>

void push(int val);
void pop();
void display();

struct node {
    int data;          
    struct node *next;  
} *top = NULL;

int main() {
    int choice, value;

    printf("******* STACK USING LINKED LIST *******\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. PUSH (Insert)\n");
        printf("2. POP (Delete)\n");
        printf("3. DISPLAY (Show Stack)\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter the value to be inserted: ");
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
                exit(0);

            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0; 
}

void push(int val) {

    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    if (newnode == NULL) {
        printf("Memory allocation failed! Stack overflow.\n");
        return;
    }

    newnode->data = val; 
    newnode->next = top;  
    top = newnode;        

    printf("Insertion successful!\n");
}


void pop() {
    if (top == NULL) { 
        printf("Stack is empty! No elements to delete.\n");
    } else {
        struct node *temp = top; 
        printf("%d is deleted.\n", temp->data); 
        top = temp->next; 
        free(temp); 
    }
}


void display() {
    if (top == NULL) { 
        printf("Stack is empty!\n");
    } else {
        struct node *temp = top;  
        printf("Stack contents: ");
        while (temp != NULL) {  
            printf("%d --> ", temp->data);  
            temp = temp->next;  
        }
        printf("NULL\n");  
    }
}
