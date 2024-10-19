#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    int i, len, c = 0;

    printf("Enter string: ");
    scanf("%s", s);

    len = strlen(s);
    
    for (i = 0; i < len / 2; i++) {
        if (s[i] == s[len - i - 1]) {
            c++;
        }
    }

    if (c == len / 2) {
        printf("String is palindrome\n");
    } else {
        printf("String is not palindrome\n");
    }

    return 0;
}

