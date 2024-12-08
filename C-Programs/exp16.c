/*

This code defines and implements a custom function mystrcmp to compare two strings and determine if they are the same or 
different.

*/

#include <stdio.h>

int mystrcmp(char str1[], char str2[]);

int main() {
    char str1[40], str2[40];

    printf("Enter first string: \n");
    scanf("%s", str1);
    printf("Enter second string: \n");
    scanf("%s", str2);

    // DIRECT METHOD
    // if (mystrcmp(str1, str2) == 0)
    //     printf("Given Strings are same\n");
    // else
    //     printf("Given Strings are different\n");

    if (strcmp(str1, str2) == 0)
        printf("Given Strings are same\n");
    else
        printf("Given Strings are different\n");

    return 0;
}

int mystrcmp(char str1[], char str2[]) {
    int i = 0;

    // Compare characters of both strings until a mismatch or end of strings
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 1;  // Strings are different
        }
        i++;
    }

    // If both strings end at the same time, they are the same
    return str1[i] == str2[i] ? 0 : 1;
}

/*

OUTPUT
--------------------------------------------------
Enter first string:
hello
Enter second string:
hello
Given Strings are same


Enter first string:
hello
Enter second string:
world
Given Strings are different

*/
