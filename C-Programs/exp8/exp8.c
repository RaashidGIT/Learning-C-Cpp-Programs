#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch;
    int vowels = 0, spaces = 0, tabs = 0, newlines = 0;
    FILE *fptr;

    // Open file for reading
    fptr = fopen("demo.txt", "r");
    if (fptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read characters from the file and count occurrences
    while ((ch = fgetc(fptr)) != EOF) {
        switch (ch) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
                vowels++;
                break;
            case ' ':
                spaces++;
                break;
            case '\t':
                tabs++;
                break;
            case '\n':
                newlines++;
                break;
        }
    }

    // Close the file
    fclose(fptr);

    // Print results
    printf("Number of vowels = %d\n", vowels);
    printf("Number of spaces = %d\n", spaces);
    printf("Number of tabs = %d\n", tabs);
    printf("Number of newlines = %d\n", newlines);

    return 0;
}



