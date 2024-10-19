#include <stdio.h>

// Function to perform Quick Sort on an array
void quicksort(int number[25], int first, int last)
{
    int i, j, pivot, temp;

    // Only sort if there is more than one element in the range
    if (first < last)
    {
        // Choose the first element as the pivot
        pivot = first;
        i = first;
        j = last;

        // Partitioning process
        while (i < j)
        {
            // Move `i` to the right while elements are less than or equal to the pivot
            while (number[i] <= number[pivot] && i < last)
                i++;
            // Move `j` to the left while elements are greater than the pivot
            while (number[j] > number[pivot])
                j--;
            
            // Swap elements if `i` is less than `j`
            if (i < j)
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }

        // Place the pivot element in its correct position
        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;

        // Recursively apply Quick Sort to the left and right sub-arrays
        quicksort(number, first, j - 1);
        quicksort(number, j + 1, last);
    }
}

int main()
{
    int i, count, number[25];

    // Print the header for Quick Sort
    printf(".............QUICKSORT...........");

    // Get the number of elements to sort
    printf("\n\tEnter the number of elements: ");
    scanf("%d", &count);

    // Ensure the number of elements does not exceed the array size
    if (count > 25) {
        printf("Error: The number of elements exceeds the maximum allowed size of 25.\n");
        return 1;
    }

    // Get the elements from the user
    printf("\n\tEnter %d elements: ", count);
    for (i = 0; i < count; i++)
        scanf("%d", &number[i]);

    // Call the Quick Sort function to sort the array
    quicksort(number, 0, count - 1);

    // Print the sorted elements
    printf("\n\tOrder of sorted elements: ");
    for (i = 0; i < count; i++)
        printf(" %d", number[i]);
    printf("\n");

    return 0;
}

