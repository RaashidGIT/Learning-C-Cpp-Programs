#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct node {
    int info;
    struct node *next;
};

// Declare the start of the linked list as a global pointer
struct node *start = NULL;

// Function prototypes
void create();
void display();
void insert_begin();
void insert_end();
void insert_pos();
void delete_begin();
void delete_end();
void delete_pos();
void search();

int main() {
    int choice;
    while (1) {
        printf("\n MENU \n");
        printf("1. Create\n");
        printf("2. Display\n");
        printf("3. Insert at the beginning\n");
        printf("4. Insert at the end\n");
        printf("5. Insert at the specified position\n");
        printf("6. Delete at beginning\n");
        printf("7. Delete at end\n");
        printf("8. Delete from specified position\n");
        printf("9. Search\n");
        printf("10. Exit\n");
        printf("________________________________\n");
        printf("Enter your choice: \t");
        scanf("%d", &choice);
        switch (choice) {
            case 1: create(); break;
            case 2: display(); break;
            case 3: insert_begin(); break;
            case 4: insert_end(); break;
            case 5: insert_pos(); break;
            case 6: delete_begin(); break;
            case 7: delete_end(); break;
            case 8: delete_pos(); break;
            case 9: search(); break;
            case 10: exit(0); break;
            default: printf("\n Invalid Choice\n"); break;
        }
    }
    return 0;
}

void create() {
    struct node *temp, *ptr;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter data value for node: ");
    scanf("%d", &temp->info);
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    } else {
        ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

void display() {
    struct node *ptr;
    if (start == NULL) {
        printf("\n List is empty \n");
        return;
    }
    ptr = start;
    printf("\n The list elements are: \n");
    while (ptr != NULL) {
        printf("%d\t", ptr->info);
        ptr = ptr->next;
    }
    printf("\n");
}

void insert_begin() {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("\n Out of memory space \n");
        return;
    }
    printf("Enter the data value for the node: ");
    scanf("%d", &temp->info);
    temp->next = start;
    start = temp;
}

void insert_end() {
    struct node *temp, *ptr;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("\n Out of memory space \n");
        return;
    }
    printf("Enter data value for the node: ");
    scanf("%d", &temp->info);
    temp->next = NULL;
    if (start == NULL) {
        start = temp;
    } else {
        ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

void insert_pos() {
    struct node *temp, *ptr;
    int i, pos;
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("\n Out of memory space \n");
        return;
    }
    printf("Enter the position for the new node to be inserted: ");
    scanf("%d", &pos);
    printf("Enter the data value for the node: ");
    scanf("%d", &temp->info);
    temp->next = NULL;

    if (pos == 0) {
        temp->next = start;
        start = temp;
    } else {
        ptr = start;
        for (i = 0; i < pos - 1; i++) {
            if (ptr == NULL) {
                printf("\n Position not found \n");
                free(temp);
                return;
            }
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        ptr->next = temp;
    }
}

void delete_begin() {
    struct node *ptr;
    if (start == NULL) {
        printf("\n List is empty\n");
        return;
    }
    ptr = start;
    start = start->next;
    printf("Deleted element is: %d\n", ptr->info);
    free(ptr);
}

void delete_end() {
    struct node *temp, *ptr;
    if (start == NULL) {
        printf("\n List is empty\n");
        return;
    } else if (start->next == NULL) {
        ptr = start;
        start = NULL;
        printf("Deleted element is: %d\n", ptr->info);
        free(ptr);
    } else {
        ptr = start;
        while (ptr->next->next != NULL) {
            ptr = ptr->next;
        }
        temp = ptr->next;
        ptr->next = NULL;
        printf("Deleted element is: %d\n", temp->info);
        free(temp);
    }
}

void delete_pos() {
    struct node *temp, *ptr;
    int i, pos;
    if (start == NULL) {
        printf("\n List is empty \n");
        return;
    }
    printf("Enter the position of node to be deleted: ");
    scanf("%d", &pos);

    if (pos == 0) {
        ptr = start;
        start = start->next;
        printf("Deleted element is: %d\n", ptr->info);
        free(ptr);
    } else {
        ptr = start;
        for (i = 0; i < pos - 1; i++) {
            if (ptr == NULL || ptr->next == NULL) {
                printf("\n Position not found \n");
                return;
            }
            ptr = ptr->next;
        }
        temp = ptr->next;
        ptr->next = temp->next;
        printf("Deleted element is: %d\n", temp->info);
        free(temp);
    }
}

void search() {
    int x, flag = 0;
    struct node *temp;
    temp = start;
    if (start == NULL) {
        printf("\n List is empty\n");
        return;
    }
    printf("Enter the value to search: ");
    scanf("%d", &x);
    while (temp != NULL) {
        if (temp->info == x) {
            printf("Data found\n");
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 0) {
        printf("Data not found in the list\n");
    }
}

