/*

This C program inserts one string (str2) into another string (str1) at a specified position.

*/

#include <stdio.h>
#include <string.h>

int main() {
    char str1[40], str2[20];
    int l1, l2, n, i;

    printf("Enter the string 1:\n");
    scanf("%s", str1);
    
    printf("Enter the string 2:\n");
    scanf("%s", str2);

    l1 = strlen(str1);
    l2 = strlen(str2);

    printf("Enter the position where the string to be inserted in:\n");
    scanf("%d", &n);

    // Check for valid position
    if (n > l1 || n < 0) {
        printf("Invalid position\n");
        return 1;
    }

    // Shift characters in str1 to make space for str2
    for (i = l1; i >= n; i--) {
        str1[i + l2] = str1[i];
    }

    // Insert str2 into str1 at position n
    for (i = 0; i < l2; i++) {
        str1[n + i] = str2[i];
    }

    // Null terminate the resulting string
    str1[l1 + l2] = '\0';

    printf("After inserting the string, str1 is: %s\n", str1);

    return 0;
}

/*

OUTPUT
-------------------------------------------------------------
Enter the string 1:
hello
Enter the string 2:
world
Enter the position where the string to be inserted in:
2

After inserting the string, str1 is: heworldllo

*/
