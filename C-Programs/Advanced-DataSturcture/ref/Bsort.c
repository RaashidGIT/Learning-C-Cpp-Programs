// modified code including error handling

#include <stdio.h>
#include <stdlib.h> // Required for exception checking

// Function to perform bubble sort
void bubbleSort(int array[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (array[j] > array[j+1]) {
                // Swap elements
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int main() {
int c, n, array[100];

    printf("Enter number of elements\n");
    if (scanf("%d", &n) != 1) {
      printf("Invalid input. Please enter an integer.\n");
      exit(EXIT_FAILURE);
   }

    printf("Enter %d integers\n", n);

    for (c = 0; c < n; c++)
      if (scanf("%d", &array[c]) != 1) {
         printf("Invalid input. Please enter an integer.\n");
         exit(EXIT_FAILURE);
      }

    // Sort the array using bubble sort
    bubbleSort(array, n);

    printf("Sorted array:\n");
    for (c = 0; c < n; c++)
        printf("%d ", array[c]);
    printf("\n");

    return 0;
}
