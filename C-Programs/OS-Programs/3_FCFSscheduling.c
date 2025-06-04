/*
 * AIM:
 * This program calculates the Waiting Time, Turnaround Time, and Completion Time
 * for a set of processes using First-Come First-Served (FCFS) scheduling.
 * It also computes the average waiting and turnaround times.

-Waiting Time: The time a process spends waiting in the ready queue before its execution begins.
-Turnaround Time: The total time from when a process arrives until it completes its execution. It's the sum of waiting time and burst time.
-Completion Time: The time at which a process finishes execution.
-First Come First Serve (FCFS): This is a non-preemptive scheduling algorithm where processes are executed in the order of their arrival times.
 
1. **Struct Declaration:**

* A `struct process` is defined to store process-related details such as:

* `id`: Process ID
* `wait`: Waiting time
* `burst`: Burst time (execution time required by the process)
* `tottime`: Turnaround time
* `comp`: Completion time
* `arrival`: Arrival time of the process
* An array `p[20]` is used to store information for a maximum of 20 processes.

2. **Input the Number of Processes:**

* The program prompts the user to input the number of processes (`n`).

3. **Input Process Details:**

* For each process (up to `n` processes), the program asks the user to input:

* Process ID (`p[i].id`)
* Arrival time (`p[i].arrival`)
* Burst time (`p[i].burst`)
* Initializing `wait`, `comp`, and `tottime` to 0 for each process.

4. **Calculation of Waiting Time, Turnaround Time, and Completion Time:**

* The **waiting time** for the first process is always `0` since it starts executing immediately.
* For subsequent processes, the **waiting time** is determined based on the previous process's **completion time** and the current process's **arrival time**:

* If the current process arrives after the previous one finishes, there is no waiting time.
* If it arrives before the previous one finishes, it has to wait.
* The **completion time** for each process is calculated as:

* Completion time = Arrival time + Waiting time + Burst time.

5. **Turnaround Time Calculation:**

* Turnaround time for each process is computed as:

* Turnaround time = Completion time - Arrival time.

6. **Calculating Totals and Averages:**

* The program calculates:

* Total wait time (`totwait`)
* Total turnaround time (`totturnaround`)
* The averages for waiting time and turnaround time are calculated as:

* `avwait = totwait / n`
* `avturn = totturnaround / n`

7. **Display Output:**

* The program prints a table of each process's details (ID, burst time, arrival time, waiting time, turnaround time, completion time).
* The averages for **waiting time** and **turnaround time** are displayed with one decimal precision.

 */

#include <stdio.h>

struct process {
    int id, wait, burst, tottime, comp, arrival;
} p[20];

void main() {
    int i, n;
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
        p[i].wait = 0; // Initialize wait time
        p[i].comp = 0; // Initialize completion time
        p[i].tottime = 0; // Initialize turnaround time
    }

    // Calculate waiting time, turnaround time, and completion time
    p[0].wait = 0;  // First process always has wait time 0
    p[0].comp = p[0].arrival + p[0].burst;  // Completion time = arrival time + burst time for the first process
    
    for (i = 1; i < n; i++) {
        // Wait time for process i is the time spent waiting before it starts execution
        if (p[i].arrival > p[i-1].comp) {
            // If the arrival time of the current process is greater than the completion time of the previous process
            p[i].wait = 0; // It will not wait
        } else {
            // Otherwise, it waits until the previous process finishes
            p[i].wait = p[i-1].comp - p[i].arrival;
        }
        
        p[i].comp = p[i].arrival + p[i].wait + p[i].burst;  // Completion time = arrival time + wait time + burst time
    }

    // Calculate total wait time, turnaround time and total turnaround time
    for (i = 0; i < n; i++) {
        p[i].tottime = p[i].comp - p[i].arrival;  // Turnaround time = completion time - arrival time
        totwait += p[i].wait;
        totturnaround += p[i].tottime;
    }

    // Calculate average waiting time and average turnaround time
    avwait = totwait / n;  // Calculate average wait time
    avturn = totturnaround / n;   // Calculate average turnaround time

    // Print process details including Completion Time, Burst Time, and Turnaround Time
    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print averages with 1 decimal point
    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
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
Enter process arrival time: 2
Enter process burst time: 1

ID	Burst Time	Arrival Time	Wait Time	Turnaround Time	Completion Time
1	    4	        0	            0	        4		           4
2	    3	        1	            3	        6		           7
3	    1	        2	            5	        6		           8
Average Waiting Time: 2.7
Average Turnaround Time: 5.3
 
*/
