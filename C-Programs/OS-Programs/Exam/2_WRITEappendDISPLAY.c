#include <stdio.h>
#include <stdlib.h>

int main() {
    char c, fname1[100], fname2[100];
    FILE *fptr1, *fptr2;

    printf("Enter the filename to open: ");
    scanf("%s", fname1);

    fptr1 = fopen(fname1, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s\n", fname1);
        exit(0);
    }

    printf("Enter the filename to append to: ");
    scanf("%s", fname2);

    fptr2 = fopen(fname2, "a");
    if (fptr2 == NULL) {
        printf("Cannot open file %s\n", fname2);
        fclose(fptr1);
        exit(0);
    }

    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    printf("\nContent in %s appended to %s\n", fname1, fname2);

    fclose(fptr1);
    fclose(fptr2);

    fptr2 = fopen(fname2, "r");
    printf("\nUpdated content of %s:\n", fname2);
    while ((c = fgetc(fptr2)) != EOF) {
        putchar(c);
    }

    fclose(fptr2);
    return 0;
}
