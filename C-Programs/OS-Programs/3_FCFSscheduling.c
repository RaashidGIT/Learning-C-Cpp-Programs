/*
 * AIM:
 * This program calculates the Waiting Time, Turnaround Time, and Completion Time
 * for a set of processes using First-Come First-Served (FCFS) scheduling.
 * It also computes the average waiting and turnaround times.
 */

#include <stdio.h>

// Structure to hold process data
struct process {
    int id;        // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int wait;      // Waiting Time
    int comp;      // Completion Time
    int tottime;   // Turnaround Time
} p[20];

int main() {
    int n, i;
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

        // Initialize times
        p[i].wait = 0;
        p[i].comp = 0;
        p[i].tottime = 0;
    }

    // First process setup
    p[0].wait = 0;
    p[0].comp = p[0].arrival + p[0].burst;

    // Calculate times for the rest of the processes
    for (i = 1; i < n; i++) {
        if (p[i].arrival > p[i - 1].comp) {
            // If CPU is idle
            p[i].wait = 0;
            p[i].comp = p[i].arrival + p[i].burst;
        } else {
            p[i].wait = p[i - 1].comp - p[i].arrival;
            p[i].comp = p[i - 1].comp + p[i].burst;
        }
    }

    // Compute turnaround and total times
    for (i = 0; i < n; i++) {
        p[i].tottime = p[i].comp - p[i].arrival;
        totwait += p[i].wait;
        totturnaround += p[i].tottime;
    }

    // Averages
    avwait = totwait / n;
    avturn = totturnaround / n;

    // Output
    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);

    return 0;
}

/*

----------------------- OUTPUT ----------------------------------

Enter the number of processes: 3

Enter process ID: 1
Enter process arrival time: 0
Enter process burst time: 4

Enter process ID: 2
Enter process arrival time: 1
Enter process burst time: 3

Enter process ID: 3
Enter process arrival time: 
2
Enter process burst time: 1

ID	Burst Time	Arrival Time	Wait Time	Turnaround Time	Completion Time
1	    4	        0	            0	        4		           4
2	    3	        1	            3	        6		           7
3	    1	        2	            5	        6		           8
Average Waiting Time: 2.7
Average Turnaround Time: 5.3
 
*/
