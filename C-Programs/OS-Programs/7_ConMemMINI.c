/*
    Aim: To simulate contiguous memory allocation in file systems.
         This program allocates memory blocks to files using contiguous allocation,
         checks for available space, and displays a directory and disk status.

    MINI VERSION - REPLACED MULTIPLE STRING ID WITH A SINGLE STRING ID TO SIMPLIFY THE PROGRAM!
*/

#include <stdio.h>      // Standard I/O functions

int num = 0;            // Counter for number of files
int len[10];            // Stores the length (number of blocks) for each file
int str[10];            // Stores the start index of each file
char fid[10];           // Stores file names (1 character per file)
char a[20];             // Represents the disk with 20 blocks; each holds a file name or '.'

// Function to display the directory table showing file name, start, and length
void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4c\t%3d\t%6d\n", fid[i], str[i], len[i]);  // Print info for each file
}

// Function to display the state of the disk
void display() {
    printf("\nDisk Space:\n");

    // Print block indices 0 to 19
    for (int i = 0; i < 20; i++)
        printf("%4d", i); // Print each index in a 4-character wide field
    printf("\n");

    // Print file names or '.' for each block
    for (int i = 0; i < 20; i++)
        printf("%4c", a[i]);  // If block is empty (.), print dot; else print file ID

    printf("\n");
}

int main() {
    char id;        // File ID (1 character)
    int st;         // Start block
    int nb;         // Number of blocks
    int ch;         // User choice to continue or not

    // Initialize all blocks as empty ('.')
    for (int i = 0; i < 20; i++)
        a[i] = '.';   // '.' represents an empty block

    // Show initial disk state
    printf("Disk space before allocation:\n");
    display();

    // Start allocation loop
    do {
        // Get file name from user (1 character only)
        printf("\nEnter file name (1 character): ");
        scanf(" %c", &id);  // Leading space skips leftover newline

        // Get starting block index
        printf("Enter the start block: ");
        scanf("%d", &st);

        // Get number of blocks required
        printf("Enter number of blocks: ");
        scanf("%d", &nb);

        // Validate that allocation stays within disk limits
        if (st < 0 || st + nb > 20) {
            printf("Requirement exceeds range.\n");
            continue;   // Retry
        }

        // Check if all blocks from st to st+nb-1 are free
        int flag = 1;   // Assume allocation is possible
        for (int i = st; i < st + nb; i++) {
            if (a[i] != '.') {   // If block already occupied
                flag = 0;
                break;
            }
        }

        // If any block is occupied, allocation fails
        if (!flag) {
            printf("Contiguous allocation not possible.\n");
            continue;   // Retry
        }

        // Record file metadata
        fid[num] = id;      // Store file ID
        len[num] = nb;      // Store number of blocks
        str[num] = st;      // Store starting index

        // Perform the allocation by marking blocks with file ID
        for (int i = st; i < st + nb; i++)
            a[i] = id;

        printf("Allocation done.\n");
        num++;  // Increment file count

        // Ask user whether to continue
        printf("Any more allocation? (1. Yes, 2. No): ");
        scanf("%d", &ch);

    } while (ch == 1);  // Repeat if user chooses 1

    // Final directory and disk status
    printf("\nContiguous Allocation:\n");
    directory();

    printf("\nDisk space after allocation:\n");
    display();

    return 0;   // End of program
}

/*

-------------------------------------SIMULATED OUTPUT--------------------------------------

Disk space before allocation:

Disk Space:
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .

Enter file name (1 character): A
Enter the start block: 2
Enter number of blocks: 5
Allocation done.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (1 character): B
Enter the start block: 10
Enter number of blocks: 6
Allocation done.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (1 character): C
Enter the start block: 4
Enter number of blocks: 5
Contiguous allocation not possible.

Enter file name (1 character): D
Enter the start block: 19
Enter number of blocks: 1
Allocation done.
Any more allocation? (1. Yes, 2. No): 2

Contiguous Allocation:

File    Start   Length
A         2          5
B        10          6
D        19          1

Disk space after allocation:

Disk Space:
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
   .   .   A   A   A   A   A   .   .   .   B   B   B   B   B   B   .   .   .   D


...Program finished with exit code 0
Press ENTER to exit console.

*/
