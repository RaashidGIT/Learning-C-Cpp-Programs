/*
 * AIM:
 * This program reads content from one file and appends it to another file.
 * After appending, it displays the full content of the destination file.
 
Algorithm: File Content Appending

1. Start
2. Initialize variables:
    char c (to store characters read from files)
    char fname1[100] (for source file name)
    char fname2[100] (for destination file name)
    FILE *fptr1, *fptr2 (file pointers for the source and destination files)
3. Prompt user for source file name:
    Display the message: "Enter the filename to open:"
    Read the source file name into fname1
4. Open the source file in read mode:
    Attempt to open fname1 using fopen(fname1, "r") and assign the file pointer to fptr1
    If the file cannot be opened (i.e., fptr1 == NULL), display the error message: "Cannot open file [filename]" and terminate the program (exit)
5. Prompt user for destination file name:
    Display the message: "Enter the filename to append to:"
    Read the destination file name into fname2
6. Open the destination file in append mode:
    Attempt to open fname2 using fopen(fname2, "a") and assign the file pointer to fptr2
    If the file cannot be opened (i.e., fptr2 == NULL), display the error message: "Cannot open file [filename]"
        Close the source file using fclose(fptr1)
        Terminate the program (exit)
7. Append content from source to destination:
    Loop through each character from the source file fptr1 until EOF:
        Read each character using fgetc(fptr1)
        Write the character to the destination file using fputc(c, fptr2)
8. Display success message:
    Display: "Content in [fname1] appended to [fname2]"
9. Close both files:
    Close fptr1 using fclose(fptr1)
    Close fptr2 using fclose(fptr2)
10. Reopen the destination file in read mode:
    Open fname2 using fopen(fname2, "r") and assign the file pointer to fptr2
11. Display the updated content of the destination file:
    Display the message: "Updated content of [fname2]:"
    Loop through each character from the destination file fptr2 until EOF:
        Read and display each character using putchar(c)
12. Close the destination file after displaying:
    Close fptr2 using fclose(fptr2)
13. End

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
