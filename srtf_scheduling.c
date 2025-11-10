#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[20], bt[20], rt[20], ct[20], wt[20], tat[20], completed[20] = {0};
    int i, time = 0, complete = 0, shortest;
    float avg_wt = 0, avg_tat = 0;
    int gantt[100], gantt_time[100], g_count = 0;

    // Input arrival and burst times
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("\n--- SRTF Scheduling ---\n");

    while (complete != n) {
        shortest = -1;
        int min_remaining = INT_MAX;

        // Find process with shortest remaining time at current time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0 && rt[i] < min_remaining && rt[i] > 0) {
                min_remaining = rt[i];
                shortest = i;
            }
        }

        if (shortest == -1) { // no process available
            time++;
            continue;
        }

        // Record Gantt chart (only when process changes)
        if (g_count == 0 || gantt[g_count - 1] != shortest)
            gantt[g_count++] = shortest;

        // Run the process for 1 time unit
        rt[shortest]--;
        time++;

        // If process completes
        if (rt[shortest] == 0) {
            completed[shortest] = 1;
            complete++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < g_count; i++)
        printf("|  P%d  ", gantt[i] + 1);
    printf("|\n0");
    time = 0;
    for (i = 0; i < g_count; i++) {
        int pid = gantt[i];
        int next_pid = (i + 1 < g_count) ? gantt[i + 1] : -1;
        int run_time = 0;

        // Count continuous run of same process
        for (int j = i; j < g_count && gantt[j] == pid; j++)
            run_time++;

        time += run_time;
        printf("\t%d", time);
    }
    printf("\n");

    return 0;
}
