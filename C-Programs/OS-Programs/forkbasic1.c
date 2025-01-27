#include<stdio.h>
#include<unistd.h>
int main(){
	fork();
	printf("Hello!\n");
	return 0;
}

/*

---------------- OUTPUT ----------------

 Hello!
 Hello!

----------------------------------------

Explanation:

    The fork() system call creates a child process, which is a duplicate of the parent process. 
    Both processes (the parent and the child) will continue execution from the point after fork(), so both will print "Hello!".
    The exact order of the output might vary depending on how the OS schedules the processes, but generally, both the parent and child processes will print "Hello!".

*/
