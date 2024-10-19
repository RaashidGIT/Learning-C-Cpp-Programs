#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
#define POSTFIXSIZE 100

typedef struct stack {
    int data[MAX];
    int top;
} stack;

void init(stack *);
int empty(stack *);
int full(stack *);
int pop(stack *);
void push(stack *, int);
int evaluate(char x, int op1, int op2);

int main() { 
    stack s;
    char x;
    int op1, op2, val;
    init(&s);
    printf("\t\tEvaluation of postfix expression\n");
    printf("\t\tEnter the expression\n");
    printf("\t\tSingle digit operand and operators only:\n");

    while ((x = getchar()) != '\n') {
        if (isdigit(x))  
            push(&s, x - '0');  
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            val = evaluate(x, op1, op2);
            push(&s, val);
        }
    }

    val = pop(&s);
    printf("\tValue of expression = %d\n", val);
    return 0;  // Return a value for 'main'
}

int evaluate(char x, int op1, int op2) {
    if (x == '+')
        return (op1 + op2);
    if (x == '-')
        return (op1 - op2);
    if (x == '*')
        return (op1 * op2);
    if (x == '/')
        return (op1 / op2);
    if (x == '%')
        return (op1 % op2);
    return 0;  // Add a default return value
}

void init(stack *s) {
    s->top = -1;
}

void push(stack *s, int x) {
    s->data[++(s->top)] = x; 
}

int pop(stack *s) {
    return s->data[(s->top)--]; 
}

