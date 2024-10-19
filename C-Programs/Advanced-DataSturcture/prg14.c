// Objective: Implement a doubly linked list with operations for insertion, deletion, display, and search.

#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *prev;
    struct node *next;
    int data;
};

struct node *head = NULL;

void insertion_beginning();
void insertion_last();
void insertion_specified();
void deletion_beginning();
void deletion_last();
void deletion_specified();
void display();
void search();

int main() {
    int choice = 0;
    while (choice != 9) {
	printf("\n---------------MENU--------------------\n");
        printf("Choose an option from the following list:\n");
        printf("1. Insertion at beginning\n");
        printf("2. Insertion at last\n");
        printf("3. Insertion at any specified location\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete from specified location\n");
        printf("7. Search\n");
        printf("8. Show\n");
        printf("9. Exit\n");
	printf("\n----------------------------------------\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: insertion_beginning(); break;
            case 2: insertion_last(); break; 
            case 3: insertion_specified(); break;
            case 4: deletion_beginning(); break;
            case 5: deletion_last(); break;
            case 6: deletion_specified(); break;
            case 7: search(); break;
            case 8: display(); break;
            case 9: exit(0);
            default: printf("Please enter a valid choice\n");
        }
    }
    return 0; 
}

void insertion_beginning() {
    struct node *ptr;
    int item;
    ptr = (struct node*)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Overflow\n");
    } else {
        printf("\nEnter item value: ");
        scanf("%d", &item);
        ptr->data = item;
        ptr->prev = NULL;
        if (head == NULL) {
            ptr->next = NULL;
            head = ptr;
        } else {
            ptr->next = head;
            head->prev = ptr;
            head = ptr;
        }
        printf("\nNode inserted\n");
    }
}

void insertion_last() {
    struct node *ptr, *temp;
    int item;    
    ptr = (struct node*)malloc(sizeof(struct node)); 
    if (ptr == NULL) {
        printf("\nOverflow\n");
    } else {
        printf("\nEnter value: ");
        scanf("%d", &item);
        ptr->data = item;
        ptr->next = NULL; 
        if (head == NULL) {
            ptr->prev = NULL;
            head = ptr;
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->prev = temp; 
        }
        printf("Node inserted\n");
    }
}

void insertion_specified() {
    struct node *ptr, *temp;
    int item, position;   
    ptr = (struct node*)malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Overflow\n");
        return;
    }   
    printf("\nEnter item value: ");
    scanf("%d", &item);
    ptr->data = item;

    printf("Enter position to insert (1 for beginning, 2 for second, etc.): ");
    scanf("%d", &position);
    if (position == 1) {
        ptr->prev = NULL;
        if (head == NULL) {
            ptr->next = NULL;
            head = ptr;
        } else {
            ptr->next = head;
            head->prev = ptr;
            head = ptr;
        }
    } else {
        // Insertion at specified position
        temp = head;
        for (int i = 1; temp != NULL && i < position - 1; i++) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Position exceeds the length of the list. Node inserted at the end instead.\n");
            ptr->next = NULL;
            if (head == NULL) {
                ptr->prev = NULL;
                head = ptr;
            } else {
                temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = ptr;
                ptr->prev = temp;
            }
        } else {
            ptr->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = ptr;
            }
            temp->next = ptr;
            ptr->prev = temp;
        }
    }   
    printf("Node inserted at position %d\n", position);
}


void deletion_beginning() {
    struct node *ptr;
    if (head == NULL) {
        printf("\nUnderflow\n");
    } else {
        ptr = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL; 
        }
        free(ptr);
        printf("Node deleted\n");
    }
}

void deletion_last() {
    struct node *ptr;
    if (head == NULL) {
        printf("\nUnderflow\n");
    } else if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Node deleted\n");
    } else {
        ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->prev->next = NULL;
        free(ptr);
        printf("Node deleted\n");
    }
}

void deletion_specified() {
    struct node *ptr;
    int position;
    printf("Enter position of the node to be deleted: ");
    scanf("%d", &position);
    if (head == NULL) {
        printf("Underflow: The list is empty.\n");
        return;
    }
    ptr = head;
    for (int i = 1; ptr != NULL && i < position; i++) {
        ptr = ptr->next; // Traverse to the desired position
    }
    if (ptr == NULL) {
        printf("Position exceeds the length of the list. Cannot delete.\n");
        return;
    }
    // Deletion logic
    if (ptr->prev != NULL) {
        ptr->prev->next = ptr->next; // Link previous node to next node
    } else {
        head = ptr->next; // If deleting the head
    }
    if (ptr->next != NULL) {
        ptr->next->prev = ptr->prev; // Link next node to previous node
    }
    free(ptr);
    printf("Node at position %d deleted\n", position);
}

void display() {
    struct node *ptr;
    printf("\nPrinting values..........\n");
    ptr = head;
    while (ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }
}

void search() {
    struct node *ptr;
    int item, i = 0, flag = 1; 
    ptr = head;
    if (ptr == NULL) {
        printf("Empty list\n");
    } else {
        printf("Enter item which you want to search: ");
        scanf("%d", &item);
        while (ptr != NULL) {
            if (ptr->data == item) {
                printf("Item found at location %d\n", i + 1);
                flag = 0; 
                break;
            }
            i++;
            ptr = ptr->next;
        }
        if (flag) {
            printf("Item not found\n");
        }
    }
}
