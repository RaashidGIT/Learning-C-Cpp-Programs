/*

Program using the following system calls: fork(), execl() and wait().

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    // Creating a child process

    if (pid < 0) {
        // Error in creating child process
        perror("Fork failed");
    } else if (pid == 0) {
        // Replacing the child process with the "ls" command
        execl("/bin/ls", "ls", "-s", NULL);

        // If execl fails
        perror("execl failed");
        exit(1); // Changed 0 to 1 to indicate an error
    } else {
        // This block is executed by the parent process
        wait(NULL); // Wait for the child process to complete
        printf("\n\t Completed!\n");
        exit(0);
    }
}


/*

----------------------------------------------------------------------
OUTPUT
----------------------------------------------------------------------

	 Completed!

*/
