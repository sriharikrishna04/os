#include <stdio.h>
#include <limits.h>

#define N 5 // Number of processes

// Function prototypes
int findHighestPriorityProcess(int priority[], int at[], int rt[], int currentTime);
void findWaitingTime(int priority[], int at[], int bt[], int wt[]);
void findTurnaroundTime(int bt[], int wt[], int tat[]);
void findAverageTime(int priority[], int at[], int bt[]);
void manualInput(int priority[], int at[], int bt[]);

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Input process details manually\n");
        printf("2. Use predefined process details\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    int priority[N], arrival_time[N], burst_time[N];
                    manualInput(priority, arrival_time, burst_time);
                    findAverageTime(priority, arrival_time, burst_time);
                }
                break;
            case 2:
                {
                    // Predefined process details
                    int arrival_time[] = {0, 1, 2, 3, 4};
                    int burst_time[] = {6, 3, 8, 4, 5};
                    int priority[] = {3, 1, 4, 5, 2};
                    findAverageTime(priority, arrival_time, burst_time);
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}

// Function to find the process with the highest priority
int findHighestPriorityProcess(int priority[], int at[], int rt[], int currentTime) {
    int highestPriority = INT_MAX;
    int highestPriorityProcess = -1;
    int i;

    for (i= 0; i < N; i++) {
        if (at[i] <= currentTime && priority[i] < highestPriority && rt[i] > 0) {
            highestPriority = priority[i];
            highestPriorityProcess = i;
        }
    }

    return highestPriorityProcess;
}

// Function to calculate waiting time for each process
void findWaitingTime(int priority[], int at[], int bt[], int wt[]) {
    int rt[N];

    // Copy burst time into remaining time
    int i;
    for (i= 0; i < N; i++) {
        rt[i] = bt[i];
    }

    int complete = 0; // Number of processes completed
    int currentTime = 0;
    int minProcess;

    // Continue until all processes are completed
    while (complete != N) {
        minProcess = findHighestPriorityProcess(priority, at, rt, currentTime);

        // If no process is available at current time
        if (minProcess == -1) {
            currentTime++;
            continue;
        }

        // Decrement remaining time for selected process
        rt[minProcess]--;

        // If a process is completed
        if (rt[minProcess] == 0) {
            complete++;
            int finishTime = currentTime + 1;
            wt[minProcess] = finishTime - bt[minProcess] - at[minProcess];
            if (wt[minProcess] < 0) {
                wt[minProcess] = 0;
            }
        }

        // Move to the next time unit
        currentTime++;
    }
}

// Function to calculate turnaround time for each process
void findTurnaroundTime(int bt[], int wt[], int tat[]) {
	int i;
    for (i= 0; i < N; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(int priority[], int at[], int bt[]) {
    int wt[N], tat[N];

    // Calculate waiting time for all processes
    findWaitingTime(priority, at, bt, wt);

    // Calculate turnaround time for all processes
    findTurnaroundTime(bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    // Display processes along with all details
    printf("Processes   Arrival Time   Burst Time   Waiting Time   Turnaround Time\n");
    int i;
    for (i= 0; i < N; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", i + 1);
        printf("            %d ", at[i]);
        printf("            %d ", bt[i]);
        printf("             %d ", wt[i]);
        printf("                %d\n", tat[i]);
    }

    // Calculate and print average waiting time and average turnaround time
    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)N);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / (float)N);
}

// Function to input process details manually
void manualInput(int priority[], int at[], int bt[]) {
    printf("Enter burst time, arrival time, and priority for each process:\n");
    int i;
    for (i = 0; i < N; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &bt[i], &at[i], &priority[i]);
    }
}

