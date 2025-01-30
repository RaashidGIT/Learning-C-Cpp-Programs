/* 

Code to mask the input with '*'

START
1. Declare a character array `pass[9]` to store 8 characters and a null terminator.
2. Print the message "Enter 8 characters".
3. FOR each character `i` from 0 to 7:
   a. Read a character from user input and store it in `pass[i]`.
   b. Print the character `*` to mask the user input.
4. Set the null terminator `'\0'` at `pass[8]` to properly end the string.
5. Print the message "Password input completed".
STOP

*/

#include<stdio.h>

void main() {
    char pass[9];  // 8 characters + 1 for null terminator
    int i;
    
    printf("Enter 8 characters:\n");
    
    for(i = 0; i < 8; i++) {
        pass[i] = getchar();  // Read each character
        printf("*");          // Print a '*' instead of the entered character
    }
    
    pass[8] = '\0'; // Null-terminate the string (optional)
    
    printf("\nPassword input completed.\n");
}

/* 

OUTPUT
-------------------------------------------------
Enter 8 characters:
abcd1234

********
Password input completed.

*/
