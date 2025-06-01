#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Maximum buffer size

int mutex = 1;        
int empty = BUFFER_SIZE; 
int full = 0;              
int buffer[BUFFER_SIZE]; 
int in = 0;                  
int out = 0;             

void wait(int *s) {
    while (*s <= 0);  
    (*s)--;         
}

void signal(int *s) {
    (*s)++; 
}

void producer() {
    int item;

    if (empty == 0) {
        printf("Buffer is full! Cannot produce.\n");
        return;
    }

    printf("Enter an item: ");
    scanf("%d", &item);

    wait(&empty); 
    wait(&mutex);  

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;  

    signal(&mutex); 
    signal(&full);   

    printf("Produced item: %d\n", item);
}

void consumer() {
    if (full == 0) {
        printf("Buffer is empty! Cannot consume.\n");
        return;
    }

    wait(&full);  
    wait(&mutex);  

    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;  

    signal(&mutex);  
    signal(&empty);  

    printf("Consumed item: %d\n", item);
}

int main() {
    int choice;

    printf("1. Producer\n2. Consumer\n3. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer(); 
                break;
            case 2:
                consumer(); 
                break;
            case 3:
                exit(0);     
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
