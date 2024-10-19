#include <stdio.h>
#include <stdlib.h>

void sequential_search(int a[], int n, int value) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] == value) {
            printf("\n%d is found at position %d", value, i + 1);
            return;
        }
    }
    printf("\n%d is not found", value);
}

void binary_search(int a[], int n, int value) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] < value)
            low = mid + 1;
        else if (a[mid] == value) {
            printf("\n%d is found at position %d", value, mid + 1);
            return;
        } else
            high = mid - 1;
    }
    printf("\n%d is not found", value);
}

int main() {
    int a[100], i, value, n;

    printf("Enter the size of array: ");
    scanf("%d", &n);

    printf("Enter the elements into array: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Elements in the array are: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nEnter the value to be searched: ");
    scanf("%d", &value);

    printf("\nSequential search\n________________\n");
    sequential_search(a, n, value);

    printf("\n\nBinary search\n______________________\n");
    binary_search(a, n, value);

    printf("\n");

    return 0;
}

