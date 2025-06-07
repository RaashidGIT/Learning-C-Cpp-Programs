/*
    Aim:
    To implement Priority Scheduling (non-preemptive) in C where processes are scheduled 
    based on their priority, and to calculate each process's waiting time, turnaround time, 
    and completion time along with average waiting and turnaround times.
---

### **Algorithm for Priority Scheduling (Non-Preemptive)**

---

#### **Step 1: Declare the Process Structure**

1. Define a structure called `process` to store details about each process:

   * `id`: A unique identifier for the process.
   * `wait`: Waiting time — how long the process waited before execution.
   * `burst`: CPU Burst Time — how long the process takes to execute.
   * `tottime`: Turnaround time — total time from arrival to completion.
   * `comp`: Completion time — when the process finished executing.
   * `arrival`: Arrival time — when the process entered the ready queue.
   * `priority`: Priority level of the process (higher number = higher priority).
   * `completed`: Boolean flag to track if the process is finished.

2. Use an array `p[20]` to store details for up to 20 processes.

---

#### **Step 2: Input the Number of Processes**

1. Prompt the user to enter the number of processes `n`.

2. For each process (from 1 to `n`), ask the user to enter:

   * Process ID
   * Arrival time
   * Burst time
   * Priority value

3. For each process, initialize:

   * `wait = 0`
   * `comp = 0`
   * `tottime = 0`
   * `completed = false`

---

#### **Step 3: Begin Priority Scheduling (Non-Preemptive)**

1. Initialize the following variables:

   * `completed = 0`: To track the number of finished processes.
   * `time = 0`: Represents the current system time.
   * `highestPriority = -1`: Used to select the process with the highest priority.

2. **Process Scheduling Loop**:
   Repeat while the number of completed processes is less than `n`:

---

#### **Step 4: Select the Highest Priority Process That Has Arrived**

1. Initialize:

   * `highest = -1`: Index of the process with the highest priority.
   * `highestPriority = -1`: Start with the lowest possible priority.

2. For each process `i` from 0 to `n-1`:

   * Check if the process has arrived (`arrival <= time`) AND not completed.
   * If so, and its priority is greater than the current `highestPriority`:

     * Update `highestPriority` to this process’s priority.
     * Set `highest = i`.

---

#### **Step 5: Execute the Selected Process**

1. If a process was found (i.e., `highest != -1`):

   * Advance system time by its burst time: `time += burst`.
   * Set `comp = time` — the process's completion time.
   * Compute `tottime = comp - arrival`.
   * Compute `wait = tottime - burst`.
   * Mark the process as `completed = true`.
   * Increment `completed` count.
   * Add `wait` to `totwait` and `tottime` to `totturnaround`.

2. If no process is ready (none have arrived):

   * Simply increment system time by 1 (`time++`) and retry.

---

#### **Step 6: Calculate Averages**

1. After all processes are completed:

   * Average Waiting Time: `avwait = totwait / n`
   * Average Turnaround Time: `avturn = totturnaround / n`

---

#### **Step 7: Display the Results**

1. Print a table showing for each process:

   * Process ID (`id`)
   * Burst Time (`burst`)
   * Arrival Time (`arrival`)
   * Priority (`priority`)
   * Waiting Time (`wait`)
   * Turnaround Time (`tottime`)
   * Completion Time (`comp`)

2. Print:

   * **Average Waiting Time**
   * **Average Turnaround Time**

---

#### **Step 8: End**

* The program finishes after scheduling and displaying all results.

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
1	    5		    0		        2		    0		      5		    5
2	    3		    1		        3		    4		      7		    8
3	    4		    2		        1		    6		    10		12

Average Waiting Time: 3.3
Average Turnaround Time: 7.3

*/
