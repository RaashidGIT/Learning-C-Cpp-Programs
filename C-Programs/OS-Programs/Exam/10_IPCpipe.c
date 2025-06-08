#include <stdio.h>      
#include <stdlib.h>    
#include <unistd.h>    
#include <sys/types.h> 

int is_prime(int n) {
    if (n <= 1) return 0; 
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; 
    }
    return 1; 
}

int main() {
    int pfd[2];         
    pid_t pid;      

    if (pipe(pfd) == -1) {
        perror("pipe"); 
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork"); 
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        close(pfd[0]);  

        int f1 = 0, f2 = 1, f3;
        for (int i = 0; i < 25; i++) {
            f3 = f1 + f2;
            write(pfd[1], &f3, sizeof(f3));  
            f1 = f2;
            f2 = f3;
        }

        close(pfd[1]);  
        exit(EXIT_SUCCESS); 
    } else {  
        close(pfd[1]);  

        int fib_num;
        printf("Parent prints Fibonacci numbers that are prime:\n");
        while (read(pfd[0], &fib_num, sizeof(fib_num)) > 0) {
            if (is_prime(fib_num)) {
                printf("%d\t", fib_num);  
            }
        }

        close(pfd[0]);  
        printf("\n");
        exit(EXIT_SUCCESS); 
    }
}
