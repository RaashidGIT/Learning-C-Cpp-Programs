/* 
   AIM: 
   To demonstrate inter-process communication using a pipe, where the child process 
   generates Fibonacci numbers and the parent process filters and prints only the 
   prime numbers from the Fibonacci series.
*/

#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For exit, EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>     // For fork, pipe, read, write
#include <sys/types.h>  // For pid_t

// Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0; // Numbers less than or equal to 1 are not prime
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // If divisible, not a prime
    }
    return 1; // If no divisors found, it is a prime
}

int main() {
    int pfd[2];         // Array to hold pipe file descriptors: pfd[0] = read end, pfd[1] = write end
    pid_t pid;          // Necessary for fork() system call

    // Create the pipe
    if (pipe(pfd) == -1) {
        perror("pipe"); // Error if pipe creation fails
        exit(EXIT_FAILURE);
    }

    // Create child process
    pid = fork();
    if (pid == -1) {
        perror("fork"); // Error if fork fails
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pfd[0]);  // Close the read end of the pipe

        int f1 = 0, f2 = 1, f3;
        // Generate 25 Fibonacci numbers
        for (int i = 0; i < 25; i++) {
            f3 = f1 + f2;
            write(pfd[1], &f3, sizeof(f3));  // Write Fibonacci number to pipe
            f1 = f2;
            f2 = f3;
        }

        close(pfd[1]);  // Close the write end after sending data
        exit(EXIT_SUCCESS); // Exit child process
    } else {  // Parent process
        close(pfd[1]);  // Close the write end of the pipe

        int fib_num;
        printf("Parent prints Fibonacci numbers that are prime:\n");
        // Read numbers from pipe and check for primality
        while (read(pfd[0], &fib_num, sizeof(fib_num)) > 0) {
            if (is_prime(fib_num)) {
                printf("%d\t", fib_num);  // Print if the number is prime
            }
        }

        close(pfd[0]);  // Close the read end after reading is done
        printf("\n");
        exit(EXIT_SUCCESS); // Exit parent process
    }
}

/*

-------------------------------SIMULATED OUTPUT---------------------------------

Parent prints Fibonacci numbers that are prime:
2       3       5       13      89      233     1597    28657

*/
