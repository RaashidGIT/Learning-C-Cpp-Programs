/*
    Aim: To simulate contiguous memory allocation in file systems.
         This program allocates memory blocks to files using contiguous allocation,
         checks for available space, and displays a directory and disk status.
*/

#include <stdio.h>      // Standard I/O functions
#include <string.h>     // For string manipulation functions like strcpy()

int num = 0;            // Counter for number of files
int len[10];            // Stores the length (number of blocks) for each file
int str[10];            // Stores the start index of each file
char fid[10][4];        // Stores file names (max 3 characters + null terminator)
char a[20][4];          // Represents the disk with 20 blocks; each holds a file name or is empty

// Function to display the directory table showing file name, start, and length
void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4s\t%3d\t%6d\n", fid[i], str[i], len[i]);  // Print info for each file
}

// Function to display the state of the disk
void display() {
    printf("\nDisk Space:\n");

    // Print block indices 0 to 19
    for (int i = 0; i < 20; i++)
        printf("%4d", i); // ensures that the integer i is printed in a column-like fashion, 
                          // aligning numbers to the right within a field of at least 4 characters.
    printf("\n");

    // Print file names or "." for each block
    for (int i = 0; i < 20; i++)
        printf("%4s", (a[i][0] == '\0') ? "." : a[i]);  // If block is empty, print ".", else print file name

    printf("\n");
}

int main() {
    char id[4];     // To store the input file name (max 3 characters)
    int st;         // Start block for file allocation
    int nb;         // Number of blocks requested by user
    int ch;         // To check whether user wants to continue

    // Initialize all disk blocks to empty by copying empty string ""
    for (int i = 0; i < 20; i++)
        strcpy(a[i], "");

    // Show disk status before any allocation
    printf("Disk space before allocation:\n");
    display();

    // Start allocation loop
    do {
        // Get file name from user (restricted to 3 characters)
        printf("\nEnter file name (max 3 characters): ");
        scanf("%3s", id);

        // Get starting block index from user
        printf("Enter the start block: ");
        scanf("%d", &st);

        // Get number of blocks required
        printf("Enter number of blocks: ");
        scanf("%d", &nb);

        // Validate if requested blocks are within disk range
        if (st < 0 || st + nb > 20) {
            printf("Requirement exceeds range.\n");
            continue;   // Skip rest and ask user again
        }

        // Check if all required blocks from st to st+nb-1 are free (contiguous and unoccupied)
        int flag = 1;   // Assume success
        for (int i = st; i < st + nb; i++) {
            if (a[i][0] != '\0') {   // If block is not empty
                flag = 0;            // Allocation not possible
                break;
            }
        }

        // If any block in the range is already taken
        if (!flag) {
            printf("Contiguous allocation not possible.\n");
            continue;   // Retry
        }

        // Save file information to directory
        strcpy(fid[num], id);    // Store file name
        len[num] = nb;           // Store file length
        str[num] = st;           // Store starting block

        // Perform the actual allocation by storing file name in each block
        for (int i = st; i < st + nb; i++)
            strcpy(a[i], id);    // Mark block with file name

        printf("Allocation done.\n");
        num++;   // Increment file count

        // Ask if user wants to allocate more files
        printf("Any more allocation? (1. Yes, 2. No): ");
        scanf("%d", &ch);

    } while (ch == 1);  // Continue if user enters 1

    // After all allocations, print directory and disk state
    printf("\nContiguous Allocation:\n");
    directory();

    printf("\nDisk space after allocation:\n");
    display();

    return 0;   // End of program
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
Allocation done.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (max 3 characters): C
Enter the start block: 10
Enter number of blocks: 3
Allocation done.
Any more allocation? (1. Yes, 2. No): 1

Enter file name (max 3 characters): D
Enter the start block: 7
Enter number of blocks: 8
Contiguous allocation not possible.

Enter file name (max 3 characters): E
Enter the start block: 18
Enter number of blocks: 1
Allocation done.
Any more allocation? (1. Yes, 2. No): 2

Contiguous Allocation:

File    Start   Length
A         2          4
B         6          3
C        10          3
E        18          1

Disk space after allocation:

Disk Space:
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
   .   .   A   A   A   A   B   B   B   .   C   C   C   .   .   .   .   .   E   .

*/
