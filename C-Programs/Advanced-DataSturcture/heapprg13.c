// Heap Sort

#include <stdio.h>

void create(int []);
void down_adjust(int [], int);

int main() { 
    int heap[30], n, i, last, temp;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("\nEnter elements: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &heap[i]);
    
    heap[0] = n;  // Set the first element as the number of elements
    create(heap);
    
    while (heap[0] > 1) {
        last = heap[0];
        temp = heap[1];
        heap[1] = heap[last];
        heap[last] = temp;
        heap[0]--;  // Decrement the count of elements
        down_adjust(heap, 1);
    }
    
    printf("Array after sorting:\n");
    for (i = 1; i <= n; i++)  // Changed loop to print in ascending order
        printf("%d ", heap[i]);  
    printf("\n");
    return 0; 
}

void create(int heap[]) {  
    int i, n;
    n = heap[0];
    for (i = n / 2; i >= 1; i--)  
        down_adjust(heap, i);
}

void down_adjust(int heap[], int i) {
    int j, temp, n;
    n = heap[0];
    while (2 * i <= n) {
        j = 2 * i;  // Left child index
        if (j + 1 <= n && heap[j + 1] > heap[j])  // If right child exists and is greater
            j = j + 1;  // Set j to right child index
        if (heap[i] >= heap[j])  // If the current node is greater than or equal to the largest child
            break;  
        // Swap the current node with the largest child
        temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        i = j;  // Move down the tree
    }
}

