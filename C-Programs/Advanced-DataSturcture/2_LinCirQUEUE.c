/*

A program that allows the user to interact with two types of queues: Linear Queue and Circular Queue.

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define SIZE 10

// Linear Queue Variables
int linearQueue[SIZE];
int frontLinear = -1;
int rearLinear = -1;

// Circular Queue Variables
int circularQueue[MAX];
int frontCircular = -1;
int rearCircular = -1;

// Function to insert into the linear queue
void enqueueLinear(int x) {
    if (rearLinear == SIZE - 1)
        printf("\nLinear Queue is full, insertion not possible.");
    else {
        if (frontLinear == -1)
            frontLinear = 0;
        rearLinear++;
        linearQueue[rearLinear] = x;
        printf("\nLinear Queue insertion successful.");
    }
}

// Function to delete from the linear queue
void dequeueLinear() {
    if (frontLinear == -1 || frontLinear > rearLinear)
        printf("\nLinear Queue is empty, deletion not possible.");
    else {
        printf("\nDeleted element from Linear Queue = %d", linearQueue[frontLinear]);
        frontLinear++;
        if (frontLinear > rearLinear)
            frontLinear = rearLinear = -1;
    }
}

// Function to display the linear queue
void displayLinear() {
    if (frontLinear == -1)
        printf("\nLinear Queue is empty");
    else {
        printf("\nElements in Linear Queue: ");
        for (int i = frontLinear; i <= rearLinear; i++)
            printf("%d  ", linearQueue[i]);
    }
}

// Function to insert into the circular queue
void insertCircular(int item) {
    if ((frontCircular == 0 && rearCircular == MAX - 1) || (frontCircular == rearCircular + 1)) {
        printf("Circular Queue overflow\n");
        return;
    }
    if (frontCircular == -1) {
        frontCircular = 0;
        rearCircular = 0;
    } else {
        if (rearCircular == MAX - 1)
            rearCircular = 0;
        else
            rearCircular++;
    }
    circularQueue[rearCircular] = item;
}

// Function to delete from the circular queue
void deleteCircular() {
    if (frontCircular == -1) {
        printf("\nCircular Queue underflow\n");
        return;
    }
    printf("\nDeleted element from Circular Queue = %d\n", circularQueue[frontCircular]);
    if (frontCircular == rearCircular) {
        frontCircular = -1;
        rearCircular = -1;
    } else {
        if (frontCircular == MAX - 1)
            frontCircular = 0;
        else
            frontCircular++;
    }
}

// Function to display the circular queue
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
}

// Main function
int main() {
    int ch, value, queueType;
    do {
        printf("\nSelect Queue Type:\n");
        printf("1. Linear Queue\n2. Circular Queue\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &queueType);

        switch(queueType) {
            case 1:
                do {
                    printf("\n--------Linear Queue MENU--------\n");
                    printf("1. Insert\n2. Delete\n3. Display\n4. Exit to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ch);
                    switch(ch) {
                        case 1: 
                            printf("\nValue to be inserted: ");
                            scanf("%d", &value);
                            enqueueLinear(value);
                            break;
                        case 2: 
                            dequeueLinear();
                            break;
                        case 3: 
                            displayLinear();
                            break;
                        case 4: 
                            break;
                        default: 
                            printf("\nInvalid choice!");
                    }
                } while(ch != 4);
                break;
            
            case 2:
                do {
                    printf("\n--------Circular Queue MENU--------\n");
                    printf("1. Insert\n2. Delete\n3. Display\n4. Exit to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ch);
                    switch(ch) {
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
                            break;
                        default:
                            printf("\nInvalid choice!");
                    }
                } while(ch != 4);
                break;

            case 3:
                break;

            default:
                printf("\nInvalid choice! Exiting program.\n");
        }
    } while(queueType != 3);

    return 0;
}

/*

OUTPUT
-----------------------------------------------------
Select Queue Type:
1. Linear Queue
2. Circular Queue
3. Exit
Enter your choice: 1

--------Linear Queue MENU--------
1. Insert
2. Delete
3. Display
4. Exit to Main Menu
Enter your choice: 1
Value to be inserted: 5
Linear Queue insertion successful.

--------Linear Queue MENU--------
1. Insert
2. Delete
3. Display
4. Exit to Main Menu
Enter your choice: 3
Elements in Linear Queue: 5

*/
