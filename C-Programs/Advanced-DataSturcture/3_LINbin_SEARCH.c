/*

This code demonstrates two search algorithms: sequential search and binary search.

Sequential_search function is called, which performs a linear scan of the array. 
It checks each element of the array one by one until the value is found or the array is fully searched.

Binary_search function is called, which assumes that the array is sorted. It uses the binary search algorithm, 
which repeatedly divides the search range in half to efficiently find the desired value.

*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[100], i, value, n, choice;

    // Get array size and elements from user
    printf("Enter the size of array: ");
    scanf("%d", &n);

    printf("Enter the elements into array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Display the entered array elements
    printf("Elements in the array are: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    // Ask user for the search method (linear or binary search)
    printf("\nChoose the search method:\n");
    printf("1. Linear Search\n2. Binary Search\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Ask for the value to be searched
    printf("Enter the value to be searched: ");
    scanf("%d", &value);

    if (choice == 1) {
        // Perform linear search
        printf("\nPerforming Linear Search...\n");
        sequential_search(a, n, value);
    } else if (choice == 2) {
        // If the array is not sorted, sort it first and then perform binary search
        sort_array(a, n);
        printf("\nPerforming Binary Search...\n");
        binary_search(a, n, value);
    } else {
        printf("\nInvalid choice! Please select 1 for Linear Search or 2 for Binary Search.\n");
    }

    return 0;
}

// Function to perform sequential search (linear search)
void sequential_search(int a[], int n, int value) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] == value) {
            printf("\n%d is found at position %d", value, i + 1);  // Index + 1 for user-friendly position
            return;
        }
    }
    printf("\n%d is not found", value);  // Value not found in the array
}

// Function to sort the array using bubble sort
void sort_array(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {  // Swap elements if out of order
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    printf("\nArray sorted successfully!\n");
}

// Function to perform binary search (array must be sorted)
void binary_search(int a[], int n, int value) {
    int low, high, mid;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (a[mid] < value)  // If value is greater than middle element, search in the right half
            low = mid + 1;
        else if (a[mid] == value) {  // If value matches the middle element, return position
            printf("\n%d is found at position %d", value, mid + 1);  // Index + 1 for user-friendly position
            return;
        } else  // If value is smaller than middle element, search in the left half
            high = mid - 1;
    }
    printf("\n%d is not found", value);  // If value is not found
}

/*

OUTPUT
-------------------------------------------------------------
Enter the size of array: 5
Enter the elements into array: 5 2 9 1 4
Elements in the array are: 5 2 9 1 4
Choose the search method:
1. Linear Search
2. Binary Search
Enter your choice: 2
Enter the value to be searched: 4

Array sorted successfully!

Performing Binary Search...

4 is found at position 3

*/
