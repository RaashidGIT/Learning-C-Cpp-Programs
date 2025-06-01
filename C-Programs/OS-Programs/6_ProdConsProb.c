/*
    Aim:
    To simulate the Producer-Consumer problem using semaphores in C, demonstrating how synchronization 
    is handled in a concurrent environment using manual semaphore logic and a circular buffer.
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Maximum buffer size

// Semaphores and shared buffer
int mutex = 1;               // Mutex for critical section access
int empty = BUFFER_SIZE;     // Tracks empty buffer slots
int full = 0;                // Tracks filled buffer slots
int buffer[BUFFER_SIZE];     // The shared buffer
int in = 0;                  // Index for the next item to be produced
int out = 0;                 // Index for the next item to be consumed

// Wait (P) operation
void wait(int *s) {
    while (*s <= 0);  // Busy wait (non-blocking)
    (*s)--;           // Decrement the semaphore
}

// Signal (V) operation
void signal(int *s) {
    (*s)++;  // Increment the semaphore
}

// Producer function
void producer() {
    int item;

    // If buffer is full, cannot produce
    if (empty == 0) {
        printf("Buffer is full! Cannot produce.\n");
        return;
    }

    // Get item input from user
    printf("Enter an item: ");
    scanf("%d", &item);

    wait(&empty);  // Decrease empty slots
    wait(&mutex);  // Enter critical section

    // Produce item into buffer
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;  // Move to next buffer position (circular)

    signal(&mutex);  // Exit critical section
    signal(&full);   // Increase full slots

    printf("Produced item: %d\n", item);
}

// Consumer function
void consumer() {
    // If buffer is empty, cannot consume
    if (full == 0) {
        printf("Buffer is empty! Cannot consume.\n");
        return;
    }

    wait(&full);   // Decrease full slots
    wait(&mutex);  // Enter critical section

    // Consume item from buffer
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;  // Move to next buffer position (circular)

    signal(&mutex);  // Exit critical section
    signal(&empty);  // Increase empty slots

    printf("Consumed item: %d\n", item);
}

// Main function with menu
int main() {
    int choice;

    // Show initial menu
    printf("1. Producer\n2. Consumer\n3. Exit\n");

    while (1) {
        // Ask user for choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle choice
        switch (choice) {
            case 1:
                producer();  // Call producer
                break;
            case 2:
                consumer();  // Call consumer
                break;
            case 3:
                exit(0);     // Exit program
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

/*
    Simulated Output Example:

    1. Producer
    2. Consumer
    3. Exit
    Enter your choice: 1
    Enter an item: 10
    Produced item: 10

    Enter your choice: 1
    Enter an item: 20
    Produced item: 20

    Enter your choice: 2
    Consumed item: 10

    Enter your choice: 2
    Consumed item: 20

    Enter your choice: 2
    Buffer is empty! Cannot consume.

    Enter your choice: 3
*/
