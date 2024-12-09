/*

This code does postfix expression evaluation
53+82-* = 48

*/

#define SIZE 50  // Define the size of the stack (maximum number of elements the stack can hold)
#include <ctype.h>
#include <stdio.h>

// Stack declaration and initialization
int s[SIZE];  // Array to store stack elements
int top = -1;  // Variable to keep track of the top index of the stack

// Function to push an element onto the stack
void push(int elem) {
    s[++top] = elem;  // Increment top index and add element to stack
}

// Function to pop an element from the stack
int pop() {
    return(s[top--]);  // Return the top element and decrease top index
}

int main() {
    char pofx[50], ch;  // Array to store the postfix expression, 'ch' for each character
    int i = 0, op1, op2;  // 'i' for index, 'op1' and 'op2' for operands

    // Input and processing
    printf("Read the postfix expression:\n");
    scanf("%s", pofx);  // Read the postfix expression from the user

    // Iterate through each character in the postfix expression
    while ((ch = pofx[i++]) != '\0') {  // Continue until end of string
        // If the character is a digit, push it onto the stack
        if (isdigit(ch)) 
            push(ch - '0');  // Convert char to int and push it onto the stack
        else {  // If the character is an operator
            op2 = pop();  // Pop the second operand
            op1 = pop();  // Pop the first operand

            // Perform the operation based on the operator
            switch (ch) {
                case '+': push(op1 + op2); break;  // Addition
                case '-': push(op1 - op2); break;  // Subtraction
                case '*': push(op1 * op2); break;  // Multiplication
                case '/': push(op1 / op2); break;  // Division
            }
        }
    }

    // Output the result of the postfix expression evaluation
    printf("\nGiven postfix expression is: %s", pofx);
    printf("\nResult after evaluation: %d", s[top]);  // The final result will be at the top of the stack

    return 0;  // End of program
}

/*

OUTPUT
---------------------------------------------------------
Evaluation of postfix expression
Enter the expression
Single digit operand and operators only:
53+82-*
Value of expression = 48

*/
