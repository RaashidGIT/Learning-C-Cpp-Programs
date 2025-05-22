#include <stdio.h>

struct process {
    int id, wait, burst, tottime, comp, arrival;
} p[20];

void main() {
    int i, n;
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
    }

    p[0].wait = 0; 
    p[0].comp = p[0].arrival + p[0].burst;  
    
    for (i = 1; i < n; i++) {
        if (p[i].arrival > p[i-1].comp) {
            p[i].wait = 0; 
        } else {
            p[i].wait = p[i-1].comp - p[i].arrival;
        }
        
        p[i].comp = p[i].arrival + p[i].wait + p[i].burst;
    }

    for (i = 0; i < n; i++) {
        p[i].tottime = p[i].comp - p[i].arrival;  
        totwait += p[i].wait;
        totturnaround += p[i].tottime;
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
