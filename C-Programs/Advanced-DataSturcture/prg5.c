#include <stdio.h>
#include <stdlib.h>

struct node { 
    int data;
    struct node *next; 
} *top = NULL;

void push() {
    struct node *newnode = (struct node*) malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("\nMemory allocation failed");
        return;
    }
    printf("\nEnter the data to be inserted: ");
    scanf("%d", &newnode->data);
    newnode->next = top;
    top = newnode;
}

void pop() {
    if (top == NULL) {
        printf("\nEmpty stack");
    } else {
        struct node *temp = top;
        printf("\nDeleted element: %d", temp->data);
        top = temp->next;
        free(temp);
    }
}

void display() {
    if (top == NULL) {
        printf("\nEmpty stack");
    } else {
        struct node *temp = top;
        printf("\nStack is: ");
        while (temp != NULL) {
            printf("%d ---> ", temp->data);
            temp = temp->next;
        }
        printf("NULL");
    }
}

int main() { 
    int ch;
    while (1) {
        printf("\n______ \n\t\tMENU\n________\n1-Insert\n2-Delete\n3-Display\n4-Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
                push();
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
                printf("Invalid choice\n");
        }
    }
    return 0; 
}

