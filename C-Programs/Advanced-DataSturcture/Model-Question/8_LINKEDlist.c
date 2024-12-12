#include <stdio.h>
#include <stdlib.h>

void insertAtPosition(int data, int position);
void search(int key);

struct node {
    int data;       
    struct node *next;
};

struct node *head = NULL;

int main() {
    int choice, data, position, key;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at Specific Position\n");
        printf("2. Search a Node\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(data, position);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                exit(0); 
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void insertAtPosition(int data, int position) {
    if (position < 0) {
        printf("Invalid position!\n");
        return;
    }

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;

    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        struct node *temp = head;
        for (int i = 0; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Position out of bounds!\n");
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;      
        }
    }
}

void search(int key) {
    struct node *temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == key) {
            printf("Node with value %d found at position %d.\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Node with value %d not found in the list.\n", key);
}
