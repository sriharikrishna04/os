#include <stdio.h>

// Function prototypes
void sortProcessesByPriority(int processes[], int n, int bt[], int pr[]);
void calculateAverageTime(int processes[], int n, int bt[], int pr[]);
void manualInput(int processes[], int bt[], int pr[], int n);

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
                // Input process details manually
                {
                    int n;
                    printf("Enter the number of processes: ");
                    scanf("%d", &n);
                    int processes[n], burst_time[n], priority[n];
                    manualInput(processes, burst_time, priority, n);
                    sortProcessesByPriority(processes, n, burst_time, priority);
                    calculateAverageTime(processes, n, burst_time, priority);
                }
                break;
            case 2:
                // Predefined process details
                {
                    // Process ids
                    int processes[] = {1, 2, 3, 4, 5};
                    int n = sizeof(processes) / sizeof(processes[0]);

                    // Burst time of all processes
                    int burst_time[] = {10, 1, 2, 1, 5};

                    // Priority of all processes (lower number means higher priority)
                    int priority[] = {3, 1, 4, 5, 2};

                    // Sort processes by priority
                    sortProcessesByPriority(processes, n, burst_time, priority);

                    // Calculate and display average time
                    calculateAverageTime(processes, n, burst_time, priority);
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

// Function to sort processes by priority
void sortProcessesByPriority(int processes[], int n, int bt[], int pr[]) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (pr[j] > pr[j+1]) {
                // Swap priorities
                temp = pr[j];
                pr[j] = pr[j+1];
                pr[j+1] = temp;

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

// Function to calculate average time
void calculateAverageTime(int processes[], int n, int bt[], int pr[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time for all processes
    wt[0] = 0; // Waiting time for first process is 0
    int i;
    for (i= 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    // Calculate turnaround time for all processes
   
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display processes along with all details
    printf("Processes   Burst Time   Priority   Waiting Time   Turnaround Time\n");

    // Calculate total waiting time and total turnaround time
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d ", processes[i]);
        printf("         %d ", bt[i]);
        printf("           %d ", pr[i]);
        printf("           %d ", wt[i]);
        printf("                %d\n", tat[i]);
    }

    // Calculate and print average waiting time and average turnaround time
    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / (float)n);
}

// Function to input process details manually
void manualInput(int processes[], int bt[], int pr[], int n) {
    printf("Enter burst time and priority for each process:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &bt[i], &pr[i]);
        processes[i] = i + 1;
    }
}

