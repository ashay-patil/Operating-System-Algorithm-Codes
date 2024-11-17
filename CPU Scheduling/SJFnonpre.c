#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int is_completed;
};

void sjfNonPreemptive(struct Process processes[], int n) {
    int completed = 0, time = 0;
    int gantt_chart[100], gc_index = 0;

    while (completed < n) {
        int index = -1;
        int min_burst = 9999;

        // Select the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].is_completed == 0 && processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                index = i;
            }
        }

        // Execute the chosen process if available
        if (index != -1) {
            time += processes[index].burst_time;
            processes[index].completion_time = time;
            processes[index].turn_around_time = time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turn_around_time - processes[index].burst_time;
            processes[index].is_completed = 1;
            completed++;
            
            // Add to Gantt chart for each time unit
            for (int j = 0; j < processes[index].burst_time; j++) {
                gantt_chart[gc_index++] = processes[index].pid;
            }
        } else {
            time++;
        }
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < gc_index; i++) printf("------");
    printf("\n | ");
    for (int i = 0; i < gc_index; i++) {
        printf("P%d | ", gantt_chart[i]);
    }
    printf("\n ");
    for (int i = 0; i < gc_index; i++) printf("------");
    printf("\n 0");
    for (int i = 1; i < gc_index + 1; i++) {
        printf("%5d", i);
    }

    // Display Results
    printf("\n\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].completion_time = 0;  // Initialize as not completed
        processes[i].is_completed = 0;
    }

    sjfNonPreemptive(processes, n);

    return 0;
}