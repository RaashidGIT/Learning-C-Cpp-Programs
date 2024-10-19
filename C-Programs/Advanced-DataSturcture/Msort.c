#include <stdio.h>

#define MAX_SIZE 10  // Define the maximum size of the array

// Function prototypes
void merge_sort(int, int);
void merge_array(int, int, int, int);

// Array to be sorted
int arr_sort[MAX_SIZE];

int main() 
{
    int i;
    printf("\n........ Merge Sort ...........\n");
    // Prompt the user to enter elements for sorting
    printf("\nEnter %d Elements for Sorting:\n", MAX_SIZE);
    
    // Read the elements from the user
    for (i = 0; i < MAX_SIZE; i++)
        scanf("%d", &arr_sort[i]);

    // Print the unsorted elements
    printf("\nThe elements are:");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("\t%d", arr_sort[i]);
    }

    // Call merge_sort to sort the array
    merge_sort(0, MAX_SIZE - 1);

    // Print the sorted elements
    printf("\nSorted elements are :");
    for (i = 0; i < MAX_SIZE; i++) 
    {
        printf("\t%d", arr_sort[i]);
    }
    printf("\n");
    return 0;
}

// Function to perform merge sort
void merge_sort(int i, int j)
{
    int m;
    // Check if there is more than one element in the range
    if (i < j) 
    {
        // Find the middle point of the array
        m = (i + j) / 2;

        // Recursively sort the first half
        merge_sort(i, m);

        // Recursively sort the second half
        merge_sort(m + 1, j);

        // Merge the sorted halves
        merge_array(i, m, m + 1, j);
    }
}

// Function to merge two sorted halves of the array
void merge_array(int a, int b, int c, int d)
{
    int t[MAX_SIZE];  // Temporary array to hold merged result
    int i = a, j = c, k = 0;

    // Merge the two halves into the temporary array
    while (i <= b && j <= d)
    {
        if (arr_sort[i] < arr_sort[j])
            t[k++] = arr_sort[i++];  // Copy element from the first half
        else
            t[k++] = arr_sort[j++];  // Copy element from the second half
    }

    // Copy any remaining elements from the first half
    while (i <= b)
        t[k++] = arr_sort[i++];

    // Copy any remaining elements from the second half
    while (j <= d)
        t[k++] = arr_sort[j++];

    // Copy the sorted elements back into the original array
    for (i = a, k = 0; i <= d; i++, k++)
        arr_sort[i] = t[k];
}

