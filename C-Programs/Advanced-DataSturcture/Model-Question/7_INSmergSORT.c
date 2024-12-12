#include <stdio.h>

void insertionSort(int arr[], int n);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main() {
    int n, choice;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i);
        scanf("%d", &arr[i]);
    }

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
            return 1; 
    }

    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right); 
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; 
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; 
    j = 0;
    k = left;

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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
