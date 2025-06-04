/*
 * AIM: 
 * This program creates a new process using fork(). The child process executes 
 * a specified command using execvp(), while the parent process waits for the 
 * child to complete before printing a completion message.

Algorithm: Execute a Program in a Child Process

1. Start
2. Check if the user has provided at least one argument (the program to execute):
    - If argc < 2:
        - Print "Usage: <program_name> <program_to_execute> [args...]"
        - Exit with failure code.
3. Create a child process using fork():
    - If pid < 0 (fork failed):
        - Print "Fork failed"
        - Exit with failure code.
4. Parent process (pid > 0):
    - Wait for the child process to finish using wait().
    - Print "Process creation completed".
    - Exit successfully.
5. Child process (pid == 0):
    - Execute the command passed as arguments using execvp(argv[1], &argv[1]).
    - If execvp fails:
        - Print "execvp failed".
        - Exit with failure code.
6. End

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the user has provided at least one argument (the program to execute)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program_to_execute> [args..]\n", argv[0]);
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
 * Running the program with `./a.out /ls` as the command:

 4 a.c	12 a.out   4 fork.c

	 Completed!

 * 
 * Process creation completed
 *
 * Running with an invalid command:
 * 
 * $ ./my_exec invalid_command
 * execvp failed: No such file or directory
 *
 */
