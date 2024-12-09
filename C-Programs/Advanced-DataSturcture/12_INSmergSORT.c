/*

This C program sorts an array using two sorting algorithms: Insertion Sort and Merge Sort.

Input Array: [5, 3, 4, 1, 2]

Insertion Sort Steps:
Step 1: [3, 5, 4, 1, 2]   // 3 inserted before 5
Step 2: [3, 4, 5, 1, 2]   // 4 inserted between 3 and 5
Step 3: [1, 3, 4, 5, 2]   // 1 inserted at the beginning
Step 4: [1, 2, 3, 4, 5]   // 2 inserted between 1 and 3

Merge Sort Steps:
1. Split into halves:
   [5, 3, 4] and [1, 2]
2. Split again:
   [5, 3] and [4], [1] and [2]
3. Sort and merge:
   [3, 5] and [4]  → [3, 4, 5]
   [1] and [2]  → [1, 2]
4. Merge the sorted halves:
   [1, 2] and [3, 4, 5] → [1, 2, 3, 4, 5]

*/

#include <stdio.h>

void insertionSort(int arr[], int n);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main() {
    int n, choice;

    // Input number of elements
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];

    // Input array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i);
        scanf("%d", &arr[i]);
    }

    // Choose sorting method
    printf("Choose sorting method:\n1. Insertion Sort\n2. Merge Sort\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            insertionSort(arr, n);
            printf("The sorted array using Insertion Sort is:\n");
            break;
        case 2:
            mergeSort(arr, 0, n - 1);
            printf("The sorted array using Merge Sort is:\n");
            break;
        default:
            printf("Invalid choice.\n");
            return 1; // Exit with error
    }

    // Display sorted array
    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

// Insertion Sort function
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid); // Sort first half
        mergeSort(arr, mid + 1, right); // Sort second half
        merge(arr, left, mid, right); // Merge the sorted halves
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid; // Size of right subarray

    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[] if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*

OUTPUT
--------------------------------------------------------
Enter the number of elements in the array: 5  
Enter the elements of the array:  
Element 0: 12  
Element 1: 4  
Element 2: 9  
Element 3: 1  
Element 4: 7  

Choose sorting method:  
1. Insertion Sort  
2. Merge Sort  
Enter your choice: 1  

The sorted array using Insertion Sort is:  
1    4    7    9    12  


Enter the number of elements in the array: 6  
Enter the elements of the array:  
Element 0: 15  
Element 1: 3  
Element 2: 8  
Element 3: 6  
Element 4: 2  
Element 5: 12  

Choose sorting method:  
1. Insertion Sort  
2. Merge Sort  
Enter your choice: 2  

The sorted array using Merge Sort is:  
2    3    6    8    12    15  

*/
