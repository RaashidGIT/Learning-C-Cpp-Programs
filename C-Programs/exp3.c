#include <stdio.h>

int main() {
    int i, j, k, n, s;
    printf("Enter number of rows:");
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        // Print spaces
        for (s = 1; s <= n - i; s++) {
            printf(" ");
        }
        
        // Print increasing numbers
        k = i;
        for (j = 1; j <= i; j++) {
            printf("%d", k++);
        }
        
        // Print decreasing numbers
        k = 2 * i - 2;
        for (j = 1; j < i; j++) {
            printf("%d", k--);
        }
        
        printf("\n");
    }
    
    return 0;
}

