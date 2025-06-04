/*
 * AIM:
 * This program implements the Shortest Job First (SJF) Non-Preemptive Scheduling Algorithm.
 * It calculates waiting time, turnaround time, and completion time for each process.

### **Algorithm for Shortest Job First (SJF) Scheduling**

#### **Step 1: Declare the Process Structure**

1. Define a structure called `process` to store details about each process:

* `id`: A unique identifier for the process.
* `wait`: The time that the process spends waiting before it starts executing.
* `burst`: The time the process requires to execute (also called the burst time).
* `tottime`: The total time taken by the process, also called the turnaround time.
* `comp`: The time when the process finishes executing, called the completion time.
* `arrival`: The time when the process arrives in the system.
* `completed`: A flag that keeps track of whether the process has finished executing or not.

2. Use an array `p[20]` to store details for up to 20 processes.

#### **Step 2: Input the Number of Processes**

1. Ask the user to input the number of processes `n`.
2. For each process (from process 1 to `n`), do the following:

* Ask the user for the process ID, arrival time, and burst time.
* Initialize `wait = 0`, `comp = 0`, `tottime = 0`, and `completed = false` for each process.

#### **Step 3: Start the Shortest Job First (SJF) Scheduling**

1. Initialize the following variables:

* `completed = 0`: Tracks the number of processes that have completed execution.
* `time = 0`: Represents the current system time (or clock time).
* 'shortest = -1': An impossibly small value that will be used to find the shortest job id.
* `minBurst = 9999`: A large value that will be used to find the shortest burst time.
2. **Process Scheduling Loop**:

* While there are still incomplete processes (`completed < n`), do the following:

3. **Find the Process with the Shortest Burst Time**:

* Look for the process that has arrived (`arrival <= time`), is not yet completed, and has the shortest burst time.
* For each process (`i` from 0 to `n-1`), check:

* If the process is ready to execute (it has arrived).
* If the process has not been completed yet.
* If the burst time of this process is shorter than the current shortest burst time (`minBurst`).
* If such a process is found, select it and set it as the process to execute.

4. **Execute the Selected Process**:

* If a process was found:

* Add its burst time to the current system time (`time += burst time`).
* Update its **completion time** as the current time (`comp = time`).
* Calculate its **turnaround time** as the difference between the completion time and the arrival time (`tottime = comp - arrival`).
* Calculate its **waiting time** as the difference between turnaround time and burst time (`wait = tottime - burst`).
* Mark the process as completed by setting `completed = true`.
* Update the totals for waiting time (`totwait`) and turnaround time (`totturnaround`).
* Increment the `completed` counter.

5. **If No Process is Ready**:

* If no process is ready to execute (none have arrived yet), simply increment the system time by 1 (`time++`) and continue checking again.

#### **Step 4: Calculate Averages**

1. Once all processes are completed (`completed == n`):

* Calculate the **average waiting time** (`avwait`) by dividing the total waiting time by the number of processes: `avwait = totwait / n`.
* Calculate the **average turnaround time** (`avturn`) by dividing the total turnaround time by the number of processes: `avturn = totturnaround / n`.

#### **Step 5: Display the Results**

1. Display a table showing the following details for each process:

* Process ID (`id`)
* Burst Time (`burst`)
* Arrival Time (`arrival`)
* Waiting Time (`wait`)
* Turnaround Time (`tottime`)
* Completion Time (`comp`)

2. After displaying the table, also display the following averages:

* **Average Waiting Time**: `avwait`
* **Average Turnaround Time**: `avturn`

#### **Step 6: End**

1. The program ends, having scheduled all processes and displayed the results.

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
1	    5		    0		        0		       5		    5
2	    3		    2		        4		       7		    9
3	    1		    4		        1		       2		    6
Average Waiting Time: 1.7
Average Turnaround Time: 4.7

*/
