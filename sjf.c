#include <stdio.h>
#include <stdlib.h>

// Function to sort processes by burst time
void sortProcessesByBurstTime(int processes[], int n, int bt[]) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (bt[j] > bt[j+1]) {
                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                // Swap process IDs
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

// Function to calculate waiting time for each process
void calculateWaitingTime(int processes[], int n, int bt[], int wt[]) {
    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculating waiting time for each process
    int i;
    for (i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding burst time and waiting time
    int i;
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void calculateAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time for all processes
    calculateWaitingTime(processes, n, bt, wt);

    // Calculate turnaround time for all processes
    calculateTurnaroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("Processes   Burst Time   Waiting Time   Turnaround Time\n");

    // Calculate total waiting time and total turnaround time
    int i;
    for (i= 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", processes[i]);
        printf("         %d ", bt[i]);
        printf("             %d ", wt[i]);
        printf("                %d\n", tat[i]);
    }

    // Calculate and print average waiting time and average turnaround time
    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / (float)n);
}

int main() {
    int choice;

    while (1) {
        printf("\nSJF Scheduling Algorithm Menu:\n");
        printf("1. Calculate with default data\n");
        printf("2. Enter custom data\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Process ids
                int processes[] = {1, 2, 3, 4, 5};
                int n = sizeof(processes) / sizeof(processes[0]);

                // Burst time of all processes
                int burst_time[] = {6, 2, 8, 3, 4};

                // Sort processes by burst time
                sortProcessesByBurstTime(processes, n, burst_time);

                calculateAverageTime(processes, n, burst_time);
                break;
            }
            case 2: {
                int n;
                printf("Enter the number of processes: ");
                scanf("%d", &n);
                if (n <= 0) {
                    printf("Invalid number of processes. Please enter a positive integer.\n");
                    break;
                }
                int processes[n];
                int burst_time[n];
                printf("Enter burst time for each process:\n");
                int i;
                for (i = 0; i < n; i++) {
                    printf("Burst time for process %d: ", i + 1);
                    scanf("%d", &burst_time[i]);
                    processes[i] = i + 1; // Process IDs starting from 1
                }
                // Sort processes by burst time
                sortProcessesByBurstTime(processes, n, burst_time);

                calculateAverageTime(processes, n, burst_time);
                break;
            }
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

