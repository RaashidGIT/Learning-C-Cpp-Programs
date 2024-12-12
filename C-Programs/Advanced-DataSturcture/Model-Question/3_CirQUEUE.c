#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void insertCircular(int item);
void deleteCircular();
void displayCircular();

int circularQueue[MAX];
int frontCircular = -1;
int rearCircular = -1;

int main() {
    int ch, value;

    do {
        printf("\n--------Circular Queue MENU--------\n");
        printf("1. Insert\n2. Delete\n3. Display\n4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\nValue to be inserted: ");
                scanf("%d", &value);
                insertCircular(value);
                break;
            case 2:
                deleteCircular();
                break;
            case 3:
                displayCircular();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (ch != 4);

    return 0;
}

void insertCircular(int item) {
    if ((frontCircular == 0 && rearCircular == MAX - 1) || (frontCircular == rearCircular + 1)) {
        printf("Circular Queue overflow\n");
        return;
    }
    if (frontCircular == -1) {
        frontCircular = 0;
        rearCircular = 0;
    } else if (rearCircular == MAX - 1) {
        rearCircular = 0; 
    } else {
        rearCircular++;
    }
    circularQueue[rearCircular] = item;
}

void deleteCircular() {
    if (frontCircular == -1) { 
        printf("\nCircular Queue underflow\n");
        return;
    }
    printf("\nDeleted element from Circular Queue = %d\n", circularQueue[frontCircular]);
    if (frontCircular == rearCircular) { 
        frontCircular = -1;
        rearCircular = -1;
    } else if (frontCircular == MAX - 1) {
        frontCircular = 0; 
    } else {
        frontCircular++;
    }
}

void displayCircular() {
    if (frontCircular == -1) { 
        printf("\nCircular Queue is empty\n");
        return;
    }
    printf("\nElements in Circular Queue: ");
    int frontPos = frontCircular, rearPos = rearCircular;

    if (frontPos <= rearPos) {
        while (frontPos <= rearPos) {
            printf("%d  ", circularQueue[frontPos]);
            frontPos++;
        }
    } else {
        while (frontPos < MAX) {
            printf("%d  ", circularQueue[frontPos]);
            frontPos++;
        }
        frontPos = 0;
        while (frontPos <= rearPos) {
            printf("%d  ", circularQueue[frontPos]);
            frontPos++;
        }
    }
    printf("\n");
}

