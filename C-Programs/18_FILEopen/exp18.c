/*

This C program reads and displays the contents of a file.

*/

#include <stdio.h>
#include <stdlib.h>

// Enter the filename to open: demo.txt

int main()
{
    char c, fname[100];
    FILE *fptr;

    printf("Enter the filename to open\n");
    scanf("%s", fname);
    
    fptr = fopen(fname, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    
    c = fgetc(fptr);
    while (c != EOF) // Loop to read the file until the end (EOF) is reached
    {
        printf("%c", c); // Print the current character
        c = fgetc(fptr); // Read the next character from the file
    }

    fclose(fptr);
    return 0;
}

/*
OUTPUT
----------------------------------------------------------
Enter the filename to open
demo.txt

Hello, world!
This is a test file.

*/
