#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

struct P {
    int AT, BT, ST[20], WT, FT, TAT, pos;
};

int quant;

void displayGanttChart(int n, struct P p[]) {
    printf("\nGantt Chart:\n");

    // Print top border of Gantt chart
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (p[i].ST[j] != -1) {
            printf("--------");
            j++;
        }
    }
    printf("\n|");

    // Print process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (p[i].ST[j] != -1) {
            printf(" P%d |", p[i].pos);
            j++;
        }
    }
    printf("\n");

    // Print bottom border of Gantt chart
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (p[i].ST[j] != -1) {
            printf("--------");
            j++;
        }
    }
    printf("\n");

    // Print timeline below Gantt chart
    printf("0");
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (p[i].ST[j] != -1) {
            printf("       %d", p[i].ST[j] + quant <= p[i].FT ? p[i].ST[j] + quant : p[i].FT);
            j++;
        }
    }
    printf("\n");
}

int main() {
    int n, i, j;

    // Taking Input
    printf("Enter the no. of processes : ");
    scanf("%d", &n);
    struct P p[n];

    printf("Enter the quantum: ");
    scanf("%d", &quant);

    printf("Enter the process numbers:\n");
    for (i = 0; i < n; i++) scanf("%d", &(p[i].pos));

    printf("Enter the Arrival time of processes:\n");
    for (i = 0; i < n; i++) scanf("%d", &(p[i].AT));

    printf("Enter the Burst time of processes:\n");
    for (i = 0; i < n; i++) scanf("%d", &(p[i].BT));

    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++) {
        b[i] = p[i].BT;
        a[i] = p[i].AT;
        for (j = 0; j < 20; j++) s[i][j] = -1;
    }

    int tot_wt = 0, tot_tat = 0;
    bool flag = false;

    // Main Round Robin scheduling loop
    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        if (!flag) {
            time++;
            continue;
        }

        j = 0;
        while (s[index][j] != -1) j++;

        if (s[index][j] == -1) {
            s[index][j] = time;
            p[index].ST[j] = time;
        }

        if (b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quant;
            b[index] -= quant;
        }

        if (b[index] > 0) a[index] = time + 0.1;

        if (b[index] == 0) {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
        }
    }

    // Display Gantt Chart
    displayGanttChart(n, p);

    // Printing process table
    printf("\nProcess\tArrival Time\tBurst Time\tStart Times\t\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t", p[i].pos, p[i].AT, p[i].BT);

        j = 0;
        while (s[i][j] != -1) {
            printf("%d ", p[i].ST[j]);
            j++;
        }
        printf("\t\t%d\t\t%d\t\t%d\n", p[i].FT, p[i].WT, p[i].TAT);
    }

    // Calculating and printing average wait time and turnaround time
    double avg_wt = tot_wt / (double)n;
    double avg_tat = tot_tat / (double)n;
    printf("\nThe average waiting time is: %.2lf\n", avg_wt);
    printf("The average turnaround time is: %.2lf\n", avg_tat);

    return 0;
}
