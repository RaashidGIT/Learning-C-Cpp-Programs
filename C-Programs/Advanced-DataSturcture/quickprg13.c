// Quick Sort

#include <stdio.h>

void quicksort(int number[50], int first, int last) {
    int i, j, pivot, temp;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (number[i] <= number[pivot] && i < last)
                i++;
            while (number[j] > number[pivot])
                j--;
            if (i < j) {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }
        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}

int main() {
    int i, count, number[25];
    printf("Enter number of elements: ");
    scanf("%d", &count);
    if (count > 25) {
        printf("Error: Maximum number of elements is 25.\n");
        return 1;
    }
    printf("\nEnter %d elements: ", count);
    for (i = 0; i < count; i++)  
        scanf("%d", &number[i]);
    quicksort(number, 0, count - 1); 
    printf("\n\tOrder of sorted elements: ");
    for (i = 0; i < count; i++)
        printf("%d ", number[i]);
    printf("\n");
    return 0;
}

