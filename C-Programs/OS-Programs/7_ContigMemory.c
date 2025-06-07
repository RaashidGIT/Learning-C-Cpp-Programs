/*
    Aim: To simulate contiguous memory allocation in file systems.
         This program allocates memory blocks to files using contiguous allocation,
         checks for available space, and displays a directory and disk status.
*/

#include <stdio.h>
#include <string.h>

int num = 0, len[10], str[10]; 
char fid[10][4], a[20][4];  // a[i] stores file names or "." for empty

// Function to print directory table
void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4s\t%3d\t%6d\n", fid[i], str[i], len[i]);
}

// Function to display the disk space
void display() {
    printf("\nDisk Space:\n");
    
    // Print block indices
    for (int i = 0; i < 20; i++)
        printf("%4d", i);
    printf("\n");

    // Print block content
    for (int i = 0; i < 20; i++)
        printf("%4s", (a[i][0] == '\0') ? "." : a[i]);
    
    printf("\n");
}

int main() {
    char id[4];
    int st, nb, ch;

    // Initialize disk blocks to empty
    for (int i = 0; i < 20; i++)
        strcpy(a[i], "");

    printf("Disk space before allocation:\n");
    display();

    do {
        // Get file name and allocation details
        printf("\nEnter file name (max 3 characters): ");
        scanf("%3s", id);

        printf("Enter the start block: ");
        scanf("%d", &st);

        printf("Enter number of blocks: ");
        scanf("%d", &nb);

        // Range validation
        if (st < 0 || st + nb > 20) {
            printf("Requirement exceeds range.\n");
            continue;
        }

        // Check for contiguous free blocks
        int flag = 1;
        for (int i = st; i < st + nb; i++) {
            if (a[i][0] != '\0') {
                flag = 0;
                break;
            }
        }

        if (!flag) {
            printf("Contiguous allocation not possible.\n");
            continue;
        }

        // Perform allocation
        strcpy(fid[num], id);
        len[num] = nb;
        str[num] = st;

        for (int i = st; i < st + nb; i++)
            strcpy(a[i], id);

        printf("Allocation done.\n");
        num++;

        // Ask if more allocation needed
        printf("Any more allocation? (1. Yes, 2. No): ");
        scanf("%d", &ch);

    } while (ch == 1);

    // Final display
    printf("\nContiguous Allocation:\n");
    directory();

    printf("\nDisk space after allocation:\n");
    display();

    return 0;
}

/*
--------- Simulated Output ---------

Disk space before allocation:

Disk Space:
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .

Enter file name (max 3 characters): A
Enter the start block: 2
Enter number of blocks: 4
Allocation done.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (max 3 characters): B
Enter the start block: 6
Enter number of blocks: 3
Contiguous allocation not possible.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (max 3 characters): B
Enter the start block: 10
Enter number of blocks: 3
Allocation done.
Any more allocation? (1. Yes, 2. No): 2

Contiguous Allocation:

File    Start   Length
A       2       4
B       10      3

Disk space after allocation:

Disk Space:
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
   .   .   A   A   A   A   .   .   .   .   B   B   B   .   .   .   .   .   .   .

*/
