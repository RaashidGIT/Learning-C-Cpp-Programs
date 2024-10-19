#include <stdio.h>
#include <ctype.h>

char stack[20];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1)
        return -1; // Return an invalid value to indicate an empty stack
    else
        return stack[top--];
}

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return -1; // Return -1 for invalid operators
}

int main() {
    char exp[20];
    char *e, x;
    printf("\t\t Infix to postfix conversion\n");
    printf("\t\t Enter the infix expression: ");
    scanf("%s", exp);
    e = exp;
    printf("\t\t The postfix expression is: ");
    
    while (*e != '\0') { // Corrected the condition here
        if (isalnum(*e))
            printf("%c", *e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')') {
            while ((x = pop()) != '(') // Fixed the condition
                printf("%c", x);
        } else {
            while (top != -1 && priority(stack[top]) >= priority(*e)) // Check if stack is not empty
                printf("%c", pop());
            push(*e);
        }
        e++;
    }

    while (top != -1) {
        printf("%c", pop());
    }
    printf("\n");
    return 0; // Changed to return 0 to indicate successful execution
}

