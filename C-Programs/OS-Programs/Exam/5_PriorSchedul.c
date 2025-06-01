#include <stdio.h>
#include <stdbool.h>

struct process {
    int id, wait, burst, tottime, comp, arrival, priority;
    bool completed; 
} p[20];

void main() {
    int n, i, completed = 0, time = 0, highestPriority;
    float totwait = 0, totturnaround = 0, avwait, avturn;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter process ID: ");
        scanf("%d", &p[i].id);
        printf("Enter process arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter process burst time: ");
        scanf("%d", &p[i].burst);
        printf("Enter process priority (higher value = higher priority): ");
        scanf("%d", &p[i].priority);
        p[i].wait = 0;
        p[i].comp = 0;
        p[i].tottime = 0;
        p[i].completed = false; 
    }

    while (completed < n) {
        int highest = -1;         
        highestPriority = -1;     

        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].priority > highestPriority) {
                highestPriority = p[i].priority;
                highest = i;
            }
        }

        if (highest != -1) {
            time += p[highest].burst;  
            p[highest].comp = time;   
            p[highest].tottime = p[highest].comp - p[highest].arrival; 
            p[highest].wait = p[highest].tottime - p[highest].burst;   
            p[highest].completed = true; 

            totwait += p[highest].wait;
            totturnaround += p[highest].tottime;
            completed++;
        } else {
            time++;
        }
    }

    avwait = totwait / n;
    avturn = totturnaround / n;

    printf("\nID\tBurst Time\tArrival Time\tPriority\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",
               p[i].id, p[i].burst, p[i].arrival, p[i].priority, p[i].wait, p[i].tottime, p[i].comp);
    }

    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}
