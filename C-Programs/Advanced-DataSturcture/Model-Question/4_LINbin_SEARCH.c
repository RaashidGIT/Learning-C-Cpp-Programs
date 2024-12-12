#include <stdio.h>
#include <stdlib.h>

void sequential_search(int a[], int n, int value);
void sort_array(int a[], int n);
void binary_search(int a[], int n, int value);

int main() {
	int a[100], i, value, n, choice;
	
	printf("Enter the size of array: ");
	scanf("%d", &n);

	printf("Enter the elements into array: ");
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	printf("Elements in the array are: ");
	for(i = 0; i < n; i++) {
		printf("%d", a[i]);
	}

	printf("\nChoose the search method:\n");
	printf("1.Linear Search\n2.Binary Search\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	printf("Enter the value to be searched: ");
	scanf("%d", &value);
	
	if(choice == 1) {

		printf("\nPerforming Linear Search...\n");
		sequential_search(a, n, value);

	} else if(choice == 2) {

		sort_array(a, n);
		printf("\nPerforming Binary Search...\n");
		binary_search(a, n, value);

	} else {
		
		printf("\nInvalid choice! Please select 1 for Linear Search or 2 for Binary Search.\n");
	}

	return 0;
}

void sequential_search(int a[], int n, int value) {
	int i;
	for (i = 0; i < n; i++) {
		if(a[i] == value) {
			printf("\n%d is found at position %d", value, i + 1);
			return;
		}
	}
	printf("\n%d is not found", value);
}

void sort_array(int a[], int n) {
	int i, j, temp;
	for(i = 0; i < n - 1; i++) {
		for(j = 0; j < n - 1; j++) {
			if(a[j] > a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j + 1] = temp;
			}
		}
	}
	printf("\nArray sorted successfully!\n");
}

void binary_search(int a[], int n, int value) {
	int low, high, mid;
	low = 0;
	high = n - 1;

	while(low <= high) {
		mid = (low + high) / 2;
		if(a[mid] < value)
			low = mid + 1;
		else if(a[mid] == value) {
			printf("\n%d is found at position %d", value, mid + 1);
			return;
		}
		else
			high = mid - 1;
	}
	printf("\n%d is not found", value);
}					
