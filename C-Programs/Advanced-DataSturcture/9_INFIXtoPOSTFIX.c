/*

This code converts an infix expression (e.g., a+b*c) to a postfix expression (e.g., abc*+) using a stack.

*/

#include <stdio.h>
#include <ctype.h>  // For isalnum() function

// Define a stack with a maximum size of 20
char stack[20];
int top = -1;

// Function to push an element onto the stack
void push(char x) {
    stack[++top] = x;
}

// Function to pop an element from the stack
char pop() {
    if (top == -1)
        return -1;  // Return -1 if the stack is empty
    else
        return stack[top--];
}

// Function to determine the precedence of operators
int priority(char x) {
    if (x == '(')
        return 0;  // Lowest precedence for '('
    if (x == '+' || x == '-')
        return 1;  // Low precedence for + and -
    if (x == '*' || x == '/')
        return 2;  // Higher precedence for * and /
    return -1;     // Return -1 for unsupported operators
}

// Main function to convert infix to postfix
int main() {
    char exp[20];  // Array to store infix expression
    char *e, x;    // Pointers to traverse the expression

    printf("\t\t Infix to Postfix Conversion\n");
    printf("\t\t Enter the infix expression: ");
    scanf("%s", exp);  // Read the infix expression from the user

    e = exp;  // Initialize the pointer to the beginning of the expression

    printf("\t\t The postfix expression is: ");

    // Traverse the entire infix expression
    while (*e != '\0') {
        // If the current character is an operand, print it
        if (isalnum(*e))
            printf("%c", *e);

        // If the current character is a left parenthesis, push it onto the stack
        else if (*e == '(')
            push(*e);

        // If the current character is a right parenthesis, pop until '(' is found
        else if (*e == ')') {
            while ((x = pop()) != '(')
                printf("%c", x);
        }

        // If the current character is an operator
        else {
            // Pop operators with equal or higher precedence from the stack
            while (top != -1 && priority(stack[top]) >= priority(*e))
                printf("%c", pop());

            // Push the current operator onto the stack
            push(*e);
        }
        e++;  // Move to the next character in the expression
    }

    // Pop any remaining operators in the stack
    while (top != -1)
        printf("%c", pop());

    printf("\n");  // Print a newline after the postfix expression
    return 0;  // Exit the program successfully
}

/*

OUTPUT
--------------------------------------------------------
Enter the infix expression: a+b*c  
The postfix expression is: abc*+  

Enter the infix expression: (a+b)*c-d  
The postfix expression is: ab+c*d-  

*/
