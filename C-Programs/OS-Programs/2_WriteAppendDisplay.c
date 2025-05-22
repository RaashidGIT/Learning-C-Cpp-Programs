/*
 * AIM:
 * This program reads content from one file and appends it to another file.
 * After appending, it displays the full content of the destination file.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    char c, fname1[100], fname2[100];
    FILE *fptr1, *fptr2;

    // Get the source file name
    printf("Enter the filename to open: ");
    scanf("%s", fname1);

    // Open the source file in read mode
    fptr1 = fopen(fname1, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s\n", fname1);
        exit(0);
    }

    // Get the destination file name
    printf("Enter the filename to append to: ");
    scanf("%s", fname2);

    // Open the destination file in append mode
    fptr2 = fopen(fname2, "a");
    if (fptr2 == NULL) {
        printf("Cannot open file %s\n", fname2);
        fclose(fptr1); // Clean up before exiting
        exit(0);
    }

    // Read from source file and append to destination file
    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    printf("\nContent in %s appended to %s\n", fname1, fname2);

    // Close both files
    fclose(fptr1);
    fclose(fptr2);

    // Reopen destination file in read mode to display the content
    fptr2 = fopen(fname2, "r");
    printf("\nUpdated content of %s:\n", fname2);
    while ((c = fgetc(fptr2)) != EOF) {
        putchar(c);
    }

    fclose(fptr2);
    return 0;
}

/*

---------------- OUTPUT ------------------------------

  Enter the filename to open
  file1.txt
  Enter the filename to append
  file2.txt
  
  Content in file1.txt appended to file2.txt
  
 <Contents of file2.txt displayed here, including the appended content from file1.txt>
 
*/
