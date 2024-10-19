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
        if (head == NULL) {
            head = ptr;
            ptr->next = head;
        } else {
            temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = ptr;
            ptr->next = head;
            head = ptr;
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
        if (head == NULL) {
            head = ptr;
            ptr->next = head;
        } else {
            temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->next = head;
        }
        printf("\nNode inserted\n");
    }
}

void begin_delete() {
    struct node *ptr;
    if (head == NULL) {
        printf("\nUnderflow\n");
    } else if (head->next == head) {
        free(head);
        head = NULL;
        printf("\nNode deleted\n");
    } else {
        ptr = head;
        while (ptr->next != head)
            ptr = ptr->next;
        ptr->next = head->next;
        free(head);
        head = ptr->next;
        printf("\nNode deleted\n");
    }
}

void last_delete() {
    struct node *ptr, *preptr;
    if (head == NULL) {
        printf("Underflow\n");
    } else if (head->next == head) {
        free(head);
        head = NULL;
        printf("\nNode deleted\n");
    } else {
        ptr = head;
        while (ptr->next != head) {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = head;
        free(ptr);
        printf("\nNode deleted\n");
    }
}

void search() {
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

void display() {
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

