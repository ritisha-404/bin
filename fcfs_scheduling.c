#include <stdio.h>

int main() {
    int n, i;
    int at[20], bt[20], ct[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sorting by arrival time (FCFS queue discipline)
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    // Calculate Completion Time
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];  // CPU idle till process arrives
        else
            ct[i] = ct[i - 1] + bt[i];
    }

    // Calculate Turnaround and Waiting Time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", i + 1);
    }
    printf("|\n0");
    for (i = 0; i < n; i++) {
        printf("\t%d", ct[i]);
    }
    printf("\n");

    return 0;
}
