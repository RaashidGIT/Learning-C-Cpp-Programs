#include <stdio.h>

int mystrcmp(char str1[40], char str2[40]);

int main() {
    char str1[40], str2[40];
    int d;
    printf("Enter first string: \n");
    scanf("%s", str1);
    printf("Enter second string: \n");
    scanf("%s", str2);
    d = mystrcmp(str1, str2);
    if(d == 0)
        printf("Given Strings are same\n");
    else
        printf("Given Strings are different\n");
    return 0;
}

int mystrcmp(char str1[40], char str2[40]) {
    int d, i, len1 = 0, len2 = 0, flag = 0;
    
    // Calculate lengths of both strings
    for(i = 0; str1[i] != '\0'; i++)
        len1++;
    for(i = 0; str2[i] != '\0'; i++)
        len2++;
    
    // Check if lengths are different
    if(len1 != len2)
        return 1;
    
    // Compare characters of both strings
    for(i = 0; i < len1; i++) {
        if(str1[i] != str2[i]) {
            flag = 1;
            break;
        }
    }
    
    if(flag == 0)
        return 0;
    else
        return 1;
}

