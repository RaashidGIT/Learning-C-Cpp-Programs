#include <stdio.h>
#define MAX_SIZE 5

// Function prototypes
void insertion_sort(int arr[]);
void merge_sort(int left, int right);
void merge_array(int a, int b, int c, int d);
void display_array(int arr[]);

int arr_sort[MAX_SIZE]; // Global array for merge sort

int main() {
    int choice, i;

    printf("Enter %d elements for sorting: \n", MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++)
        scanf("%d", &arr_sort[i]);

    printf("\nOriginal Elements: ");
    display_array(arr_sort);

    while (1) {
        printf("\n\nSorting Menu:");
        printf("\n1. Insertion Sort");
        printf("\n2. Merge Sort");
        printf("\n3. Display Elements");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertion_sort(arr_sort);
                break;
            case 2:
                merge_sort(0, MAX_SIZE - 1);
                printf("\nSorted using Merge Sort: ");
                display_array(arr_sort);
                break;
            case 3:
                printf("\nCurrent Elements: ");
                display_array(arr_sort);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to perform insertion sort
void insertion_sort(int arr[]) {
    int i, j, t, a;

    printf("\nSorting using Insertion Sort:");
    for (i = 1; i < MAX_SIZE; i++) {
        t = arr[i];
        j = i - 1; 
        while (j >= 0 && arr[j] > t) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = t;

        printf("\nIteration %d: ", i);
        for (a = 0; a < MAX_SIZE; a++) {
            printf("\t%d", arr[a]);
        }
    }
    printf("\nSorted using Insertion Sort: ");
    display_array(arr);
}

// Function to perform merge sort
void merge_sort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge_array(left, mid, mid + 1, right);
    }
}

// Function to merge two sorted arrays
void merge_array(int a, int b, int c, int d) {
    int t[MAX_SIZE];
    int i = a, j = c, k = 0;

    while (i <= b && j <= d) {
        if (arr_sort[i] < arr_sort[j])
            t[k++] = arr_sort[i++];
        else
            t[k++] = arr_sort[j++];
    }

    while (i <= b)
        t[k++] = arr_sort[i++];
    while (j <= d)
        t[k++] = arr_sort[j++];

    for (i = a, j = 0; i <= d; i++, j++)
        arr_sort[i] = t[j];
}

// Function to display the array elements
void display_array(int arr[]) {
    for (int i = 0; i < MAX_SIZE; i++)
        printf("\t%d", arr[i]);
    printf("\n");
}
