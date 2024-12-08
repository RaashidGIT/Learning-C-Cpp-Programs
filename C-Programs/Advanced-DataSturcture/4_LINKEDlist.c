/*

This C program implements a Singly Linked List with various operations that can be performed on the list.

*/

#include <stdio.h>
#include <stdlib.h>

// Node structure to represent each element in the linked list
struct node {
    int data;          // Data field to store the value of the node
    struct node *next; // Pointer to the next node in the list
};

// Function prototypes
void insertAtBeginning(int data);
void insertAtEnd(int data);
void insertAtPosition(int data, int position);
void deleteAtBeginning();
void deleteAtEnd();
void deleteAtPosition(int position);
void search(int key);
void display();

// Head pointer for the linked list
struct node *head = NULL;

int main() {
    int choice, data, position, key;

    // Infinite loop to continuously show the menu
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Specific Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Specific Position\n");
        printf("7. Search a Node\n");
        printf("8. Display List\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Switch case for handling different menu choices
        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtBeginning(data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
            case 4:
                deleteAtBeginning();
                break;
            case 5:
                deleteAtEnd();
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(position);
                break;
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 8:
                display();
                break;
            case 9:
                exit(0); // Exit the program
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to insert a node at the beginning of the linked list
void insertAtBeginning(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = head; // New node points to the current head
    head = newNode;       // New node becomes the new head
}

// Function to insert a node at the end of the linked list
void insertAtEnd(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL; // New node will be the last node, so next is NULL
    
    if (head == NULL) { // If list is empty, new node becomes the head
        head = newNode;
    } else {
        struct node *temp = head;
        // Traverse to the last node
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // Last node points to the new node
    }
}

// Function to insert a node at a specific position in the linked list
void insertAtPosition(int data, int position) {
    if (position < 0) { // Invalid position
        printf("Invalid position!\n");
        return;
    }

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;

    // Insert at the beginning (position 0)
    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        struct node *temp = head;
        // Traverse to the node just before the specified position
        for (int i = 0; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }

        // If the position is out of bounds
        if (temp == NULL) {
            printf("Position out of bounds!\n");
            free(newNode);
        } else {
            newNode->next = temp->next; // New node points to the next node
            temp->next = newNode;       // Previous node points to the new node
        }
    }
}

// Function to delete a node at the beginning of the linked list
void deleteAtBeginning() {
    if (head == NULL) { // If the list is empty
        printf("List is empty, nothing to delete.\n");
        return;
    }
    struct node *temp = head;
    head = head->next; // Move head to the next node
    free(temp);        // Free memory of the old head node
    printf("Deleted node from the beginning.\n");
}

// Function to delete a node at the end of the linked list
void deleteAtEnd() {
    if (head == NULL) { // If the list is empty
        printf("List is empty, nothing to delete.\n");
        return;
    }

    if (head->next == NULL) { // If there's only one node
        free(head);
        head = NULL;
        printf("Deleted the only node in the list.\n");
        return;
    }

    struct node *temp = head;
    // Traverse to the second-to-last node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next); // Free the memory of the last node
    temp->next = NULL; // Make the second-to-last node the last node
    printf("Deleted node from the end.\n");
}

// Function to delete a node at a specific position in the linked list
void deleteAtPosition(int position) {
    if (position < 0) { // Invalid position
        printf("Invalid position!\n");
        return;
    }

    if (head == NULL) { // If the list is empty
        printf("List is empty, nothing to delete.\n");
        return;
    }

    struct node *temp = head;

    // If deleting the first node (position 0)
    if (position == 0) {
        head = temp->next; // Change head to the next node
        free(temp);        // Free the old head node
        printf("Deleted node at position %d.\n", position);
        return;
    }

    // Traverse to the node just before the specified position
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // If position is out of bounds
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds!\n");
        return;
    }

    struct node *next = temp->next->next;
    free(temp->next); // Free the memory of the node to be deleted
    temp->next = next; // Unlink the deleted node
    printf("Deleted node at position %d.\n", position);
}

// Function to search for a node with a specific key
void search(int key) {
    struct node *temp = head;
    int position = 0;

    // Traverse the list to find the key
    while (temp != NULL) {
        if (temp->data == key) { // If the key is found
            printf("Node with value %d found at position %d.\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    // If key is not found
    printf("Node with value %d not found in the list.\n", key);
}

// Function to display all nodes in the linked list
void display() {
    struct node *temp = head;
    if (temp == NULL) { // If the list is empty
        printf("The list is empty.\n");
        return;
    }

    // Traverse the list and print the data of each node
    printf("The linked list: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data); // Print the data of the current node
        temp = temp->next; // Move to the next node
    }
    printf("NULL\n"); // Indicate the end of the linked list
}


