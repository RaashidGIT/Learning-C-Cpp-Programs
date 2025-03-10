#include <stdio.h>
#include <ctype.h>

char stack[20];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1)
        return -1;
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
    return -1;    
}

int main() {
    char exp[20];  
    char *e, x;   

    printf("\t\t Infix to Postfix Conversion\n");
    printf("\t\t Enter the infix expression: ");
    scanf("%s", exp); 
    e = exp; 

    printf("\t\t The postfix expression is: ");


    while (*e != '\0') {
 
        if (isalnum(*e))
            printf("%c", *e);

        else if (*e == '(')
            push(*e);

        else if (*e == ')') {
            while ((x = pop()) != '(')
                printf("%c", x);
        }

        else {
            while (top != -1 && priority(stack[top]) >= priority(*e))
                printf("%c", pop());

            push(*e);
        }
        e++;
    }

    while (top != -1)
        printf("%c", pop());

    printf("\n"); 
    return 0;
}
