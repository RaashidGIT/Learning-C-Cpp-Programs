#include <stdio.h>

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
    scanf("%d", &n);

    printf("Enter %d integers\n", n);

    for (c = 0; c < n; c++)
        scanf("%d", &array[c]);

    // Sort the array using bubble sort
    bubbleSort(array, n);

    printf("Sorted array:\n");
    for (c = 0; c < n; c++)
        printf("%d ", array[c]);
    printf("\n");

    return 0;
}
