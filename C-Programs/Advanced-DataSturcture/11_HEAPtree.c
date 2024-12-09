/*

This code implements a Max-Heap data structure using a static array in C. 
A max-heap is a complete binary tree where each parent node is greater than or equal to its child nodes.

*/

#include <stdio.h>
#include <stdlib.h>

int arr[100], n = 0;

// Main function with menu-driven options
int main() {
    int choice, num;

    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Quit\nEnter your choice: ");
        scanf("%d", &choice);  // Take user input for the desired action
        switch (choice) {
            case 1:  // Insert option
                printf("Enter the number to be inserted: ");
                scanf("%d", &num);
                insert(num);  // Call insert function to add element
                break;
            case 2:  // Delete option
                printf("Enter the number to be deleted: ");
                scanf("%d", &num);
                del(num);  // Call delete function to remove element
                break;
            case 3:  // Display option
                display();  // Show current heap
                break;
            case 4:  // Exit option
                exit(0);  // Exit the program
            default:
                printf("Invalid choice\n");  // Handle invalid choice
        }
    }
}

// Function to display the current heap elements
void display() {
    if (n == 0) {
        printf("Heap is empty\n");  // If heap is empty, display a message
        return;
    }
    for (int i = 0; i < n; i++)  // Iterate over heap array
        printf("%d ", arr[i]);  // Print each element
    printf("\n");
}

// Function to insert an element into the heap
void insert(int num) {
    int loc = n;  // Start insertion at the last position of the heap
    int par;

    // Move up the heap to find the correct position for the new element
    while (loc > 0) {
        par = (loc - 1) / 2;  // Calculate parent index
            if (num <= arr[par]) {  // If the number is smaller than or equal to the parent
                arr[loc] = num;  // Place the number at the current location
                n++;  // Increase the size of the heap
                return;
            }
        arr[loc] = arr[par];  // Move parent down to the current location
        loc = par;  // Move to the parent
    }
    arr[0] = num;  // If reached root, insert the number at the root
    n++;  // Increase heap size
}

// Function to delete a specified number from the heap
void del(int num) {
    int i, temp, left, right;

    // Search for the element to delete in the heap
    for (i = 0; i < n; i++) {
        if (num == arr[i])  // If element is found
            break;
    }

    if (i == n) {  // If the element is not found
        printf("%d is not found in heap\n", num);
        return;
    }

    arr[i] = arr[n - 1];  // Replace the deleted element with the last element
    n--;  // Decrease heap size

    // If the element is not the root, check if heap properties are violated
    if (i > 0) {
        int par = (i - 1) / 2;
        if (arr[i] > arr[par]) {  // If the moved element is greater than its parent
            insert(arr[i]);  // Insert the moved element to restore heap properties
            return;
        }
    }

    // Heapify down to maintain the max-heap property
    left = 2 * i + 1;
    right = 2 * i + 2;

    // Compare with children to restore heap property
    while (left < n) {
        if (right < n && arr[right] > arr[left]) {
            if (arr[i] >= arr[right]) return;  // No need to swap if heap property is maintained
            temp = arr[i];  // Swap with the larger child
            arr[i] = arr[right];
            arr[right] = temp;
            i = right;  // Move to the right child
        } else {
            if (arr[i] >= arr[left]) return;  // No need to swap
            temp = arr[i];  // Swap with the left child
            arr[i] = arr[left];
            arr[left] = temp;
            i = left;  // Move to the left child
        }
        left = 2 * i + 1;  // Update left child index
        right = 2 * i + 2;  // Update right child index
    }

    // Handle the case when only the left child is available
    if (left == n && arr[i] < arr[left - 1]) {
        temp = arr[i];
        arr[i] = arr[left - 1];
        arr[left - 1] = temp;
    }
}

/*

OUTPUT
----------------------------------------------------------------------------
1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 1
Enter the number to be inserted: 50

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 1
Enter the number to be inserted: 30

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 1
Enter the number to be inserted: 70

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 3
70 30 50 

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 2
Enter the number to be deleted: 30

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 3
70 50 

1.Insert
2.Delete
3.Display
4.Quit
Enter your choice: 4


*/
