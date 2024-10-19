// Merge sort

#include <stdio.h>
#define MAX_SIZE 5

void merge_sort(int, int);
void merge_array(int, int, int, int);
int arr_sort[MAX_SIZE];

int main() {
    int i;
    printf("\n\tEnter %d elements for sorting: \n", MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++)
        scanf("%d", &arr_sort[i]); // Removed \t from scanf
    printf("\nElements are: ");
    for (i = 0; i < MAX_SIZE; i++)
        printf("\t%d", arr_sort[i]);

    merge_sort(0, MAX_SIZE - 1); // Fixed call to merge_sort
    printf("\nSorted elements are: ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf("\t%d", arr_sort[i]);
    }
    return 0; // Added return statement to main
}

void merge_sort(int left, int right) { // Changed parameter names to left and right
    if (left < right) {
        int mid = (left + right) / 2; // Corrected mid calculation
        merge_sort(left, mid);
        merge_sort(mid + 1, right); // Changed to mid + 1
        merge_array(left, mid, mid + 1, right);
    }
}

void merge_array(int a, int b, int c, int d) {
    int t[5];
    int i = a, j = c, k = 0; // Initialize j and k correctly
    while (i <= b && j <= d) { // Changed to j <= d
        if (arr_sort[i] < arr_sort[j])
            t[k++] = arr_sort[i++];
        else
            t[k++] = arr_sort[j++];
    }
    while (i <= b)
        t[k++] = arr_sort[i++];
    while (j <= d) // Changed from <+ to <=
        t[k++] = arr_sort[j++];
    for (i = a, j = 0; i <= d; i++, j++) // Corrected loop to use j properly
        arr_sort[i] = t[j];
}

