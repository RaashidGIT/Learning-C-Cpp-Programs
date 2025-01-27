#include<stdio.h>
#include<stdlib.h>

// Purpose: This program simulates the producer-consumer problem using semaphores to manage buffer access.
// A producer generates items and places them in a shared buffer, while a consumer consumes those items.

#define BUFFERSIZE 10
int mutex, n, empty, full = 0, item;
int buffer[20];
int in = 0, out = 0, mutex = 1;

// Wait function to simulate semaphore 'wait' operation
void wait(int *s) {
    while (*s < 0) {
        printf("\nCannot add an item\n");
        exit(0);
    }
    (*s)--;
}

// Signal function to simulate semaphore 'signal' operation
void signal(int *s) {
    (*s)++;
}

// Producer function
void producer() {
    do {
        wait(&empty);  // Wait if buffer is full
        wait(&mutex);  // Wait if another process is accessing the buffer
        
        // Produce an item
        printf("Enter an item:\n");
        scanf("%d", &item);
        buffer[in] = item;
        in = (in + 1) % n;  // Update the buffer index cyclically
        
        signal(&mutex);  // Signal that the buffer is available
        signal(&full);   // Signal that the buffer has an item
        
    } while (in != n);  // Repeat until the buffer is full
}

// Consumer function
void consumer() {
    do {
        wait(&full);   // Wait if buffer is empty
        wait(&mutex);  // Wait if another process is accessing the buffer
        
        // Consume an item
        item = buffer[out];
        printf("\nConsumed item=%d\n", item);
        out = (out + 1) % n;  // Update the buffer index cyclically
        
        signal(&mutex);  // Signal that the buffer is available
        signal(&empty);  // Signal that there is space in the buffer
        
    } while (out != n);  // Repeat until the buffer is empty
}

// Main function
void main() {
    // Get the number of items to be produced and consumed
    printf("Enter the value of n (buffer size and number of items): ");
    scanf("%d", &n);
    
    empty = n;  // Initially, the buffer is empty
    
    // Produce items until the buffer is full
    while (in != n)
        producer();
    
    // Consume items until the buffer is empty
    while (in != out)
        consumer();
}

/*

------------------ OUTPUT ------------------------

 Enter the value of n (buffer size and number of items): 5
 
 Enter an item:
 10
 Enter an item:
 20
 Enter an item:
 30
 Enter an item:
 40
 Enter an item:
 50
 
 Consumed item=10
 Consumed item=20
 Consumed item=30
 Consumed item=40
 Consumed item=50

/*
