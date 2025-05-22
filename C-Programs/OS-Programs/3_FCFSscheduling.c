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

  Enter the number of processes:
  3
 
  Enter process id:
  1
  Enter service time:
  5
 
  Enter process id:
  2
  Enter service time:
  3
 
  Enter process id:
  3
  Enter service time:
  8
 
  ID              Service         Wait            Total
  1               5               0               5
  2               3               5               8
  3               8               8               16
 
  Average waiting time: 4
  Average turnaround time: 9
 
*/
