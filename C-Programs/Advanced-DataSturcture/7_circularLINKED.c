/*

This program shows how to create and manage a circular linked list in C.

*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

void beginsert();
void lastinsert();
void begin_delete();
void last_delete();
void display();
void search();

int main() {
    int choice = 0;
    while (choice != 7) {
        printf("\n---------------MAIN MENU----------------\n");
        printf("Choose one option from the following list....\n");
        printf("\n1-Insert in beginning\n2-Insert at last\n3-Delete from beginning\n4-Delete from last\n5-Search\n6-Show\n7-Exit\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: beginsert(); break;
            case 2: lastinsert(); break;
            case 3: begin_delete(); break;
            case 4: last_delete(); break;
            case 5: search(); break;
            case 6: display(); break;
            case 7: exit(0); break;
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}

void beginsert() {
    struct node *ptr, *temp;
    int item;
    ptr = (struct node*)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("\nOverflow\n");
    } else {
        printf("Enter the node data: ");
        scanf("%d", &item);
        ptr->data = item;

        if (head == NULL) {  // If the list is empty
            head = ptr;
            ptr->next = head;  // Circular reference
        } else {
            temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = ptr;  // Link last node to new node
            ptr->next = head;  // New node points to head
            head = ptr;        // Update head
        }
        printf("\nNode inserted\n");
    }
}

void lastinsert() {
    struct node *ptr, *temp;
    int item;
    ptr = (struct node*)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("\nOverflow\n");
    } else {
        printf("Enter data: ");
        scanf("%d", &item);
        ptr->data = item;

        if (head == NULL) {  // If the list is empty
            head = ptr;
            ptr->next = head;  // Circular reference
        } else {
            temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = ptr;  // Link last node to new node
            ptr->next = head;  // New node points to head
        }
        printf("\nNode inserted\n");
    }
}

void begin_delete() {
    struct node *ptr;
    if (head == NULL) {  // List is empty
        printf("\nUnderflow\n");
    } else if (head->next == head) {  // Only one node
        free(head);
        head = NULL;
        printf("\nNode deleted\n");
    } else {  // Multiple nodes
        ptr = head;
        while (ptr->next != head)
            ptr = ptr->next;
        ptr->next = head->next;  // Skip the first node
        free(head);  // Delete the first node
        head = ptr->next;  // Update head
        printf("\nNode deleted\n");
    }
}

void last_delete() {
    struct node *ptr, *preptr;
    if (head == NULL) {  // List is empty
        printf("Underflow\n");
    } else if (head->next == head) {  // Only one node
        free(head);
        head = NULL;
        printf("\nNode deleted\n");
    } else {  // Multiple nodes
        ptr = head;
        while (ptr->next != head) {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = head;  // Update last node
        free(ptr);  // Delete last node
        printf("\nNode deleted\n");
    }
}

void search() { // Searches for a specific item in the list and prints the location(s).
    struct node *ptr;
    int item, i = 0, flag = 1;
    ptr = head;

    if (ptr == NULL) {
        printf("Empty list\n");
    } else {
        printf("Item you want to search: ");
        scanf("%d", &item);

        do {
            if (ptr->data == item) {
                printf("Item found at location: %d\n", i + 1);
                flag = 0;
                break;
            }
            i++;
            ptr = ptr->next;
        } while (ptr != head);

        if (flag != 0) {
            printf("Item not found\n");
        }
    }
}

void display() { // Traverses the list and prints each node's data.
    struct node *ptr;
    ptr = head;
    if (head == NULL) {
        printf("Nothing to print\n");
    } else {
        printf("\nPrinting values---\n");
        do {
            printf("%d\n", ptr->data);
            ptr = ptr->next;
        } while (ptr != head);
    }
}

/*

OUTPUT
----------------------------------------------------------------------------
---------------MAIN MENU----------------
1-Insert in beginning
2-Insert at last
3-Delete from beginning
4-Delete from last
5-Search
6-Show
7-Exit

Enter choice: 1
Enter the node data: 10

Node inserted

Enter choice: 2
Enter data: 20

Node inserted

Enter choice: 6

Printing values---
10
20

*/
