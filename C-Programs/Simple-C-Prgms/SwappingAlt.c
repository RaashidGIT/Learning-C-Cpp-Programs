#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a = 20, b = 30;

    a = a + b;  // Add a and b and store the result in a
    b = a - b;  // Subtract b from the new value of a and store the result in b
    a = a - b;  // Subtract the new value of b from the new value of a and store the result in a

    printf("a:%d b:%d", a, b);
    return 0;
}