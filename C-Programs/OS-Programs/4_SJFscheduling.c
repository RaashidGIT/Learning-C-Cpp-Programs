/*

 * This program implements the Shortest Job First (SJF) scheduling algorithm in C.
 * It calculates the waiting time and turnaround time for a set of processes based on their service time.

*/

#include<stdio.h>

// Structure to represent a process in the scheduling queue
struct ff {
    int pid;    // Process ID
    int wait;   // Waiting time
    int ser;    // Service time (burst time)
    int temp;   // Temporary variable for sorting (optional, not used in the final logic)
} p[20], temp;

void main() {
    int i, j, n, tot = 0, totwait = 0, avwait, tturn = 0, aturn;

    // Input: Number of processes
    printf("Enter no of processes\n");
    scanf("%d", &n);

    // Input: Process ID and service time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the process id\n");
        scanf("%d", &p[i].pid);
        printf("Enter service time\n");
        scanf("%d", &p[i].ser);
        p[i].wait = 0; // Initialize waiting time to 0
    }

    // Sorting processes by their service time using Bubble Sort
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].ser > p[j].ser) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Display header for process table
    printf("\n\nPID\t SER\t WAIT\t TOT\t\n");

    // Calculate waiting time and turnaround time for each process
    for (i = 0; i < n; i++) {
        tot = tot + p[i].ser;       // Update total service time (cumulative)
        tturn = tturn + tot;       // Update total turnaround time
        if (i + 1 < n) {
            p[i + 1].wait = tot;  // Set the waiting time for the next process
        }
        totwait = totwait + p[i].wait; // Update total waiting time

        // Display process details
        printf("%d\t %d\t %d\t %d\t\n", p[i].pid, p[i].ser, p[i].wait, tot);
    }

    // Calculate average waiting time and turnaround time
    avwait = totwait / n;
    aturn = tturn / n;

    // Display total and average metrics
    printf("\nTotal waiting time: %d\n", totwait);
    printf("Average waiting time: %d\n", avwait);
    printf("Total turnaround time: %d\n", tturn);
    printf("Average turnaround time: %d\n", aturn);
}

/*

--------------------- OUTPUT ---------------------------

 Enter no of processes
 3

 Enter the process id
 1
 Enter service time
 5

 Enter the process id
 2
 Enter service time
 2

 Enter the process id
 3
 Enter service time
 8


 PID     SER     WAIT    TOT
 2       2       0       2
 1       5       2       7
 3       8       7       15

 Total waiting time: 9
 Average waiting time: 3
 Total turnaround time: 24
 Average turnaround time: 8

*/
