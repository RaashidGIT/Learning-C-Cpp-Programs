/*

This C program copies the content from one file and appends it to another file, then displays the updated content of the second file.

*/

#include <stdio.h>
#include <stdlib.h> // provides functions for general-purpose utilities

int main()
{
    char c, fname1[100], fname2[100];
    FILE *fptr1, *fptr2;

    // Open the first file for reading
    printf("Enter the filename to open\n");
    scanf("%s", fname1);
    fptr1 = fopen(fname1, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s for reading\n", fname1);
        exit(1); // Use non-zero exit code for errors
    }

    // Open the second file for appending
    printf("Enter the filename to append\n");
    scanf("%s", fname2);
    fptr2 = fopen(fname2, "a"); // Open the second file in append mode
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s for appending\n", fname2);
        fclose(fptr1); // Close the first file before exiting
        exit(1); // Use non-zero exit code for errors
    }

    // Append content from the first file to the second file
    c = fgetc(fptr1); // Read the first character from the first file
    while (c != EOF) // Continue until the end of the first file
    {
        fputc(c, fptr2); // Write the character to the second file
        c = fgetc(fptr1); // Read the next character
    }

    printf("\nContent in %s appended to %s\n\n\n", fname1, fname2);

    // Close files
    fclose(fptr1);
    fclose(fptr2);

    // Open the second file for reading and display its content
    fptr2 = fopen(fname2, "r");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s for reading\n", fname2);
        exit(1); // Use non-zero exit code for errors
    }

    // Read and display the content of the second file
    while ((c = fgetc(fptr2)) != EOF) // Continue reading until end of file
    {
        printf("%c", c);
    }

    // Close the second file
    fclose(fptr2);

    return 0;
}

/*

OUTPUT
------------------------------------------------------
Enter the filename to open  
demo1.txt  

Enter the filename to append  
demo2.txt  


Content in demo1.txt appended to demo2.txt  

Updated content of demo2.txt:  
[Contents of demo2.txt printed here]

*/
