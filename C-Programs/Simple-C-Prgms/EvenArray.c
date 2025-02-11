#include <stdio.h>
int main() {
    int staticArray[10]; // Declare a static array with a size of 10
    // Initialize the elements of the static array
    for (int i = 0; i < 10; i++) {
        staticArray[i] = i * 2;
    }
    // Print the elements of the staticArray
    printf("Elements of the static array:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", staticArray[i]);
    }
    return 0;
}