/*
 * AIM: 
 * This program creates a new process using fork(). The child process executes 
 * a specified command using execvp(), while the parent process waits for the 
 * child to complete before printing a completion message.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the user has provided at least one argument (the program to execute)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program_to_execute> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        wait(NULL);  // Wait for the child process to complete
        printf("\nProcess creation completed\n");  // Notify that execution is complete
        exit(EXIT_SUCCESS);
    } 
    else if (pid == 0) {
        // Child process
        execvp(argv[1], &argv[1]);  // Execute the given program with arguments
        perror("execvp failed");  // If execvp fails, print an error message
        exit(EXIT_FAILURE);
    } 
    else {
        // Fork failed
        perror("Fork failed");  // Print error if fork() fails
        exit(EXIT_FAILURE);
    }
}

/*
 * Simulated Output:
 *
 * Running the program with `ls -l` as the command:
 * 
 * $ ./my_exec ls -l
 * total 12
 * -rwxr-xr-x 1 user user  16784 Mar 23 12:00 my_exec
 * -rw-r--r-- 1 user user   1024 Mar 23 11:59 program.c
 * 
 * Process creation completed
 *
 * Running with an invalid command:
 * 
 * $ ./my_exec invalid_command
 * execvp failed: No such file or directory
 *
 */
