/*

This code checks whether a given string is a palindrome. 
A palindrome is a word or phrase that reads the same forward and backward (e.g., "racecar", "madam").

*/

#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    int i, len;

    printf("Enter string: ");
    scanf("%s", s);

    len = strlen(s);
    
    for (i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) {
            printf("String is not palindrome\n");
            return 0;
        }
    }
    printf("String is palindrome\n");
    return 0;
}

/*

OUTPUT
-------------------------------------------------------------
Enter string: madam
String is palindrome

Enter string: hello
String is not palindrome

*/
