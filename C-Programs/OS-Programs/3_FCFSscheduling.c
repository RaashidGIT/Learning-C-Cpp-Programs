#include<stdio.h>

// Structure to represent a process with its ID, wait time, service time, and total turnaround time
struct process {
    int id, wait, ser, tottime;
} p[20];

void main() {
    int i, n, totwait = 0, totser = 0, avturn, avwait;

    // Prompt the user to enter the number of processes
    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    // Input process details: ID and service time
    for (i = 0; i < n; i++) {
        printf("\nEnter process id:\n");
        scanf("%d", &p[i].id);
        printf("Enter service time:\n");
        scanf("%d", &p[i].ser);
    }

    // Initialize the waiting time for the first process (it's always 0)
    p[0].wait = 0;
    p[0].tottime = p[0].ser; // Total turnaround time for the first process is its service time

    // Calculate waiting time and turnaround time for each process
    for (i = 1; i < n; i++) {
        // Waiting time for the current process is the sum of the service times of all previous processes
        p[i].wait = p[i - 1].wait + p[i - 1].ser;
        // Total turnaround time is the wait time plus the service time for the current process
        p[i].tottime = p[i].wait + p[i].ser;
    }

    // Calculate total waiting time and total turnaround time for all processes
    for (i = 0; i < n; i++) {
        totwait += p[i].wait;
        totser += p[i].tottime;
    }

    // Calculate average waiting time and average turnaround time
    avturn = totser / n;
    avwait = totwait / n;

    // Display the process table
    printf("\nID\t\tService\t\tWait\t\tTotal\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].ser, p[i].wait, p[i].tottime);
    }

    // Display average waiting time and average turnaround time
    printf("Average waiting time: %d\n", avwait);
    printf("Average turnaround time: %d\n", avturn);
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
