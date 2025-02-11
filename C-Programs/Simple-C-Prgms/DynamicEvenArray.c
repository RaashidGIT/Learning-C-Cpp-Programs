#include <stdio.h>
#include <stdlib.h>
int main() {
    int* dynamicArray; // Declare a pointer to int (the type of elements in the array)
    int size; // Declare a variable to hold the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    // Allocate memory for the dynamic array
    dynamicArray = (int*)malloc(size * sizeof(int));
    if (dynamicArray == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1; // Exit the program with an error code
    }
    // Now, you can use the dynamicArray just like a regular array
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 2;
    }
    // Print the elements of the dynamicArray
    printf("Elements of the dynamic array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamicArray[i]);
    }
    // Don't forget to free the allocated memory when you're done
    free(dynamicArray);
    return 0;
}