#include <stdio.h>
#include <stdbool.h>

struct process {
    int id, wait, burst, tottime, comp, arrival;
    bool completed;
} p[20];

void main() {
    int n, i, j, completed = 0, time = 0, minBurst;
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
        p[i].wait = 0;
        p[i].comp = 0;
        p[i].tottime = 0;
        p[i].completed = false;
    }

    while (completed < n) {
        int shortest = -1;
        minBurst = 9999;

        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                shortest = i;
            }
        }

        if (shortest != -1) {
            time += p[shortest].burst;
            p[shortest].comp = time;
            p[shortest].tottime = p[shortest].comp - p[shortest].arrival;
            p[shortest].wait = p[shortest].tottime - p[shortest].burst;
            p[shortest].completed = true;

            totwait += p[shortest].wait;
            totturnaround += p[shortest].tottime;
            completed++;
        } else {
            time++;
        }
    }

    avwait = totwait / n;
    avturn = totturnaround / n;

    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d",
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}
