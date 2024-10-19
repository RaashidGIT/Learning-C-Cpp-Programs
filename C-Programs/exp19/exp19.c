#include <stdio.h>
#include <stdlib.h>

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
    fptr2 = fopen(fname2, "a");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s for appending\n", fname2);
        fclose(fptr1); // Close the first file before exiting
        exit(1); // Use non-zero exit code for errors
    }

    // Append content from the first file to the second file
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c, fptr2);
        c = fgetc(fptr1);
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
    while ((c = fgetc(fptr2)) != EOF)
    {
        printf("%c", c);
    }

    // Close the second file
    fclose(fptr2);

    return 0;
}

