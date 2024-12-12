#include <stdio.h>

void quickSort(int arr[], int low, int high);
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void printArray(int arr[], int n);

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr1[n], arr2[n];

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i]; 
    }

    printf("\nOriginal Array for Quick Sort: ");
    printArray(arr2, n);

    quickSort(arr2, 0, n - 1);
    printf("Sorted Array using Quick Sort: ");
    printArray(arr2, n);

    return 0;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); 
    return i + 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

