// Insertion sort

#include <stdio.h>
#define MAX_SIZE 5

void insertion(int arr[]);

int main() {
    int arr_sort[MAX_SIZE], i, j, a, t;
    printf("Simple insertion sort example array\n");
    printf("\nEnter %d elements for sorting:\n", MAX_SIZE);
    
    for (i = 0; i < MAX_SIZE; i++)
        scanf("%d", &arr_sort[i]);
    
    printf("\nYour data: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("\t%d", arr_sort[i]); 
    }

    for (i = 1; i < MAX_SIZE; i++) {
        t = arr_sort[i];
        j = i - 1; 
        while (j >= 0 && arr_sort[j] > t) {
            arr_sort[j + 1] = arr_sort[j];
            j = j - 1;
        }
        arr_sort[j + 1] = t;
        printf("\nIteration %d: ", i);
        for (a = 0; a < MAX_SIZE; a++) {
            printf("\t%d", arr_sort[a]);
        }
    }

    printf("\nSorted data: "); 
    for (i = 0; i < MAX_SIZE; i++) {
        printf("\t%d", arr_sort[i]);
    }
    
    return 0;
}

