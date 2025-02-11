#include <stdio.h>
int main() {
    int a, b;
    printf("Enter two numbers to swap:\n");
    printf("Enter the first number (a): ");
    scanf("%d", &a);
    printf("Enter the second number (b): ");
    scanf("%d", &b);
    printf("\nBefore swapping: a = %d, b = %d\n", a, b);
    // Swap the values without using a temporary variable
    a = a + b;
    b = a - b;
    a = a - b;
    printf("After swapping: a = %d, b = %d\n", a, b);
    return 0;
}
//This program takes two integer inputs, swaps their values without using a temporary variable, and then prints the values before and after the swap.
