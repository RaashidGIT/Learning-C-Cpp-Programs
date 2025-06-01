/*
    Aim:
    To implement Priority Scheduling (non-preemptive) in C where processes are scheduled 
    based on their priority, and to calculate each process's waiting time, turnaround time, 
    and completion time along with average waiting and turnaround times.
*/

#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct process {
    int id, wait, burst, tottime, comp, arrival, priority;
    bool completed; // To mark whether the process is completed
} p[20];

void main() {
    int n, i, completed = 0, time = 0, highestPriority;
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
        printf("Enter process priority (higher value = higher priority): ");
        scanf("%d", &p[i].priority);
        p[i].wait = 0; // Initialize wait time
        p[i].comp = 0; // Initialize completion time
        p[i].tottime = 0; // Initialize turnaround time
        p[i].completed = false; // Mark process as not completed
    }

    // Priority Scheduling Logic (non-preemptive)
    while (completed < n) {
        int highest = -1;         // Index of the process with the highest priority
        highestPriority = -1;     // Start with lowest possible priority

        // Select the highest priority process that has arrived and not completed
        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].priority > highestPriority) {
                highestPriority = p[i].priority;
                highest = i;
            }
        }

        if (highest != -1) {
            // Process the selected highest-priority job
            time += p[highest].burst;  // Advance time by the burst time
            p[highest].comp = time;    // Completion time
            p[highest].tottime = p[highest].comp - p[highest].arrival; // Turnaround time
            p[highest].wait = p[highest].tottime - p[highest].burst;   // Wait time
            p[highest].completed = true; // Mark as completed

            // Update totals
            totwait += p[highest].wait;
            totturnaround += p[highest].tottime;
            completed++;
        } else {
            time++; // If no process is ready, advance time
        }
    }

    // Calculate averages
    avwait = totwait / n;
    avturn = totturnaround / n;

    // Print process details
    printf("\nID\tBurst Time\tArrival Time\tPriority\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",
               p[i].id, p[i].burst, p[i].arrival, p[i].priority, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print average times
    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}

/*

Enter the number of processes: 3

Enter process ID: 1
Enter process arrival time: 0
Enter process burst time: 5
Enter process priority (higher value = higher priority): 2

Enter process ID: 2
Enter process arrival time: 1
Enter process burst time: 3
Enter process priority (higher value = higher priority): 3

Enter process ID: 3
Enter process arrival time: 2
Enter process burst time: 4
Enter process priority (higher value = higher priority): 1

ID	Burst Time	Arrival Time	Priority	Wait Time	Turnaround Time	Completion Time
1	      5		        0		          2		      0		        5		            5
2	      3		        1 	          3		      4		        7		            8
3	      4		        2		          1		      6		        10		          12
Average Waiting Time: 3.3
Average Turnaround Time: 7.3

*/
