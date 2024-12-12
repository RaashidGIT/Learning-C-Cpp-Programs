#include <stdio.h>
#include <ctype.h>
#define SIZE 50

int top = -1;
int s[SIZE];

void push(int elem) {
    if (top >= SIZE - 1) {
        printf("\nStack Overflow\n");
        return;
    }
    s[++top] = elem;
}

int pop() {
    if (top < 0) {
        printf("\nStack Underflow\n");
        return -1;
    }
    return s[top--];
}

int main() {
    char pofx[SIZE], ch;
    int i = 0, op1, op2;

    printf("Enter the postfix expression:\n");
    scanf("%s", pofx); 

    while ((ch = pofx[i++]) != '\0') { 
        if (isdigit(ch)) {
            push(ch - '0');
        } else { 
            op2 = pop(); 
            op1 = pop(); 

            switch (ch) {
                case '+': push(op1 + op2); break;  
                case '-': push(op1 - op2); break;  
                case '*': push(op1 * op2); break;  
                case '/': 
                    if (op2 == 0) {
                        printf("\nError: Division by zero\n");
                        return 1;
                    }
                    push(op1 / op2); 
                    break; 
                default:
                    printf("\nError: Invalid operator '%c'\n", ch);
                    return 1;
            }
        }
    }

    printf("\nGiven postfix expression is: %s", pofx);
    printf("\nResult after evaluation: %d\n", pop());

    return 0;
}

