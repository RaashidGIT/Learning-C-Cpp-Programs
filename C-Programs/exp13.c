#include <stdio.h>
#include <string.h>

char str[100], sub[100];
int count = 0, count1 = 0;

int main() {
    int i, j, l1, l2;

    printf("Enter a string: ");
    scanf("%[^\n]s", str);

    // Clear input buffer
    while (getchar() != '\n');

    printf("Enter a substring: ");
    scanf("%[^\n]s", sub);

    l1 = strlen(str);
    l2 = strlen(sub);

    i = 0;
    while (i <= l1 - l2) {
        j = 0;
        while (j < l2 && str[i + j] == sub[j]) {
            j++;
        }
        if (j == l2) {
            count1++;
            i += l2; // Move past this occurrence
        } else {
            i++;
        }
    }

    printf("%s occurs %d times in %s\n", sub, count1, str);

    return 0;
}

