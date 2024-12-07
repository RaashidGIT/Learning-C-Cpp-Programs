/*

This program reads a text file named demo.txt and counts special characters.

START
1. Declare variables:
   - Character `ch`
   - Integers `vowels`, `spaces`, `tabs`, `newlines` (initialize to 0)
   - File pointer `fptr`
2. Open the file "demo.txt" for reading:
   - IF the file cannot be opened:
     - Print "Error opening file"
     - EXIT program
3. WHILE there are characters left to read from the file:
   - READ the next character into `ch`
   - IF `ch` is a vowel ('a', 'e', 'i', 'o', 'u'):
       - Increment `vowels`
   - ELSE IF `ch` is a space (' '):
       - Increment `spaces`
   - ELSE IF `ch` is a tab ('\t'):
       - Increment `tabs`
   - ELSE IF `ch` is a newline ('\n'):
       - Increment `newlines`
4. Close the file.
5. Print:
   - "Number of vowels: vowels"
   - "Number of spaces: spaces"
   - "Number of tabs: tabs"
   - "Number of newlines: newlines"
STOP

*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char ch;
    int vowels = 0, spaces = 0, tabs = 0, newlines = 0;
    FILE *fptr;

    // Open file for reading
    if ((fptr = fopen("demo.txt", "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Count occurrences of vowels, spaces, tabs, and newlines
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            vowels++;
        else if (ch == ' ')
            spaces++;
        else if (ch == '\t')
            tabs++;
        else if (ch == '\n')
            newlines++;
    }

    fclose(fptr); // Close file

    // Print results
    printf("Number of vowels: %d\n", vowels);
    printf("Number of spaces: %d\n", spaces);
    printf("Number of tabs: %d\n", tabs);
    printf("Number of newlines: %d\n", newlines);

    return 0;
}

/*

OUTPUT
-------------------------------------------------------------
Hello World
This is a test
	With a tab
And newlines

Number of vowels: 7
Number of spaces: 7
Number of tabs: 1
Number of newlines: 4

*/


