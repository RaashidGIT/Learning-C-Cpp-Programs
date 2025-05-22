/*
 * AIM:
 * This program implements the Shortest Job First (SJF) Non-Preemptive Scheduling Algorithm.
 * It calculates waiting time, turnaround time, and completion time for each process.
 */

#include <stdio.h>
#include <stdbool.h>

// Structure to hold process information
struct process {
    int id, wait, burst, tottime, comp, arrival;
    bool completed; // To mark whether the process is completed
} p[20];

void main() {
    int n, i, j, completed = 0, time = 0, minBurst;
    float totwait = 0, totturnaround = 0, avwait, avturn;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input details for each process
    for (i = 0; i < n; i++) {
        printf("\nEnter process ID: ");
        scanf("%d", &p[i].id);
        printf("Enter process arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter process burst time: ");
        scanf("%d", &p[i].burst);
        p[i].wait = 0;
        p[i].comp = 0;
        p[i].tottime = 0;
        p[i].completed = false;
    }

    // SJF Scheduling Logic
    while (completed < n) {
        int shortest = -1;
        minBurst = 9999;

        // Find the process with the shortest burst time that has arrived and is not completed
        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                shortest = i;
            }
        }

        if (shortest != -1) {
            // Process the selected shortest job
            time += p[shortest].burst;
            p[shortest].comp = time;
            p[shortest].tottime = p[shortest].comp - p[shortest].arrival;
            p[shortest].wait = p[shortest].tottime - p[shortest].burst;
            p[shortest].completed = true;

            // Update totals
            totwait += p[shortest].wait;
            totturnaround += p[shortest].tottime;
            completed++;
        } else {
            // If no process is ready to execute, advance time
            time++;
        }
    }

    // Calculate averages
    avwait = totwait / n;
    avturn = totturnaround / n;

    // Print process details
    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d",
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print averages
    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}

/*

--------------------- OUTPUT ---------------------------

Enter the number of processes: 3

Enter process ID: 1
Enter process arrival time: 0
Enter process burst time: 5

Enter process ID: 2
Enter process arrival time: 2
Enter process burst time: 3

Enter process ID: 3
Enter process arrival time: 4
Enter process burst time: 1

ID	Burst Time	Arrival Time	Wait Time	Turnaround Time	Completion Time
1	    5		    0		        0		        5		    5
2	    3		    2		        4		        7		    9
3	    1		    4		        1		        2		    6
Average Waiting Time: 1.7
Average Turnaround Time: 4.7

*/
