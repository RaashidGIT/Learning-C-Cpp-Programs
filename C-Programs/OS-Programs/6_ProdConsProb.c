/*
    Aim:
    To simulate the Producer-Consumer problem using semaphores in C, demonstrating how synchronization 
    is handled in a concurrent environment using manual semaphore logic and a circular buffer.

## 🧠 **Algorithm: Producer–Consumer Problem using Semaphores (Non-threaded Simulation in C)**

### 🔹 **Step 1: Initialize Global Resources**

1. Define `BUFFER_SIZE` as the maximum number of items the buffer can hold.
2. Initialize semaphores:

   * `mutex = 1` → ensures **mutual exclusion** for buffer access.
   * `empty = BUFFER_SIZE` → counts available **empty slots** in buffer.
   * `full = 0` → counts available **filled slots**.
3. Initialize a `buffer[]` array of size `BUFFER_SIZE`.
4. Set `in = 0` and `out = 0` to manage circular indexing for producer and consumer respectively.

---

### 🔹 **Step 2: Define Semaphore Operations**

1. `wait(S)`:

   * If `S <= 0`, the process **waits** (here, simulated by a busy-wait).
   * Else, decrement `S` (i.e., `S--`).
2. `signal(S)`:

   * Increment the semaphore value (`S++`).

---

### 🔹 **Step 3: Producer Algorithm**

1. Check if `empty == 0`:

   * If true, print `"Buffer is full"` and return.
2. Accept input item from the user.
3. Perform:

   * `wait(empty)` → ensure space is available.
   * `wait(mutex)` → enter **critical section**.
4. Place the item into `buffer[in]`.
5. Update `in = (in + 1) % BUFFER_SIZE` (circular buffer logic).
6. Perform:

   * `signal(mutex)` → exit critical section.
   * `signal(full)` → indicate a new item was added.
7. Print confirmation: `"Produced item: X"`.

---

### 🔹 **Step 4: Consumer Algorithm**

1. Check if `full == 0`:

   * If true, print `"Buffer is empty"` and return.
2. Perform:

   * `wait(full)` → ensure item is available.
   * `wait(mutex)` → enter **critical section**.
3. Retrieve item from `buffer[out]`.
4. Update `out = (out + 1) % BUFFER_SIZE`.
5. Perform:

   * `signal(mutex)` → exit critical section.
   * `signal(empty)` → indicate a slot is now free.
6. Print confirmation: `"Consumed item: X"`.

---

### 🔹 **Step 5: Main Menu Loop**

1. Show options:

   * `1. Producer`
   * `2. Consumer`
   * `3. Exit`
2. Read user’s choice and:

   * Call `producer()` if `1`.
   * Call `consumer()` if `2`.
   * Exit program if `3`.
   * Show error message if invalid choice.

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
