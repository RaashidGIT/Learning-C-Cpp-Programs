#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char ch;

    // Check for correct number of arguments
    if (argc != 3)
    {
        printf("\nInsufficient arguments\n");
        exit(EXIT_FAILURE);
    }

    // Open the input file for reading
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        printf("\nUnable to open input file\n");
        exit(EXIT_FAILURE);
    }

    // Open the output file for writing
    fp2 = fopen(argv[2], "w");
    if (fp2 == NULL)
    {
        printf("\nUnable to open output file\n");
        fclose(fp1); // Close the input file before exiting
        exit(EXIT_FAILURE);
    }

    // Copy content from input file to output file
    while ((ch = fgetc(fp1)) != EOF)
    {
        fputc(ch, fp2);
    }

    printf("\nFile successfully copied\n");

    // Close the files
    fclose(fp1);
    fclose(fp2);

    return 0;
}

