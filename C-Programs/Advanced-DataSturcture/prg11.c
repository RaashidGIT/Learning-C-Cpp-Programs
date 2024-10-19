#include <stdio.h>
#include <stdlib.h>

int arr[100], n = 0;

void display() {
    if (n == 0) {
        printf("Heap is empty\n");
        return;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insert(int num) { 
    int loc = n;  // Start insertion at the end
    int par;

    while (loc > 0) {
        par = (loc - 1) / 2;
        if (num <= arr[par]) {
            arr[loc] = num;
            n++;  // Increment size of heap
            return;
        }
        arr[loc] = arr[par];
        loc = par;
    }
    arr[0] = num;  // Insert at the root
    n++;  // Increment size of heap
}

void del(int num) {
    int i, temp, left, right;

    for (i = 0; i < n; i++) {
        if (num == arr[i])
            break;
    }

    if (i == n) {  // Changed condition to check if num was found
        printf("%d is not found in heap\n", num);
        return;
    }

    arr[i] = arr[n - 1];  // Replace with last element
    n--;  // Decrement size of heap

    if (i > 0) {
        int par = (i - 1) / 2;
        if (arr[i] > arr[par]) {
            insert(arr[i]);  // Insert the moved element
            return;
        }
    }

    left = 2 * i + 1;
    right = 2 * i + 2;

    while (left < n) {
        if (right < n && arr[right] > arr[left]) {
            if (arr[i] >= arr[right]) return;  // No need to swap
            temp = arr[i];
            arr[i] = arr[right];
            arr[right] = temp;
            i = right;
        } else {
            if (arr[i] >= arr[left]) return;  // No need to swap
            temp = arr[i];
            arr[i] = arr[left];
            arr[left] = temp;
            i = left;
        }
        left = 2 * i + 1;
        right = 2 * i + 2;
    }

    // Handle the case when only the left child is available
    if (left == n && arr[i] < arr[left - 1]) {
        temp = arr[i];
        arr[i] = arr[left - 1];
        arr[left - 1] = temp;
    }
}

int main() {
    int choice, num;

    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Quit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the number to be inserted: ");
                scanf("%d", &num);
                insert(num);
                break;
            case 2:
                printf("Enter the number to be deleted: ");
                scanf("%d", &num);
                del(num);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}

