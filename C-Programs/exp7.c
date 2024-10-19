#include<stdio.h>
int main(){
	int i, n, temp, j, a[10];
	printf("Enter number of elements: ");
	scanf("%d", &n);
	printf("Enter %d elements: ", n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("\n array: ");
	for(i = 0; i < n; i++)
		printf("%d  ", a[i]);
	for(i = 0; i < n-1; i++){
		for(j = 0; j < n-1; j++){
			if(a[j] > a [j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	printf("\n Sorted array: ");
	for(i = 0; i < n; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");
	return 0;
}

