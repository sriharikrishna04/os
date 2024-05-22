#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_PHILOSOPHERS 10
int i,j;
// Define semaphores for each fork
sem_t forks[MAX_PHILOSOPHERS];

// Initialize all semaphores
void init(int numPhilosophers) {
    for ( i = 0; i < numPhilosophers; i++) {
        sem_init(&forks[i], 0, 1); // Initialize forks as available
    }
}

// Function for a philosopher to pick up forks
void pickForks(int p_id, int numPhilosophers) {
    sem_wait(&forks[p_id]); // Wait for left fork
    sem_wait(&forks[(p_id + 1) % numPhilosophers]); // Wait for right fork
}

// Function for a philosopher to put down forks
void putDownForks(int p_id, int numPhilosophers) {
    sem_post(&forks[p_id]); // Release left fork
    sem_post(&forks[(p_id + 1) % numPhilosophers]); // Release right fork
}

// Function for a philosopher to think
void think(int p_id) {
    printf("Philosopher %d is thinking\n", p_id);
    sleep(1); // Think for some time
}

// Function for a philosopher to eat
void eat(int p_id) {
    printf("Philosopher %d is eating\n", p_id);
    sleep(1); // Eat for some time
}

// Function to simulate a philosopher's behavior
void simulateDining(int numPhilosophers, int numTimesEat) {
    for ( i = 0; i < numTimesEat; i++) {
        for ( j = 0; j < numPhilosophers; j++) { 
            think(j);
            pickForks(j, numPhilosophers);
            eat(j);
            putDownForks(j, numPhilosophers);
        }
    }
}

int main() {
    int choice, numPhilosophers, numTimesEat;
    
    printf("Enter the number of philosophers (maximum %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &numPhilosophers);

    if (numPhilosophers < 2 || numPhilosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Please choose between 2 and %d.\n", MAX_PHILOSOPHERS);
        return 1;
    }

    init(numPhilosophers);

    printf("Enter the number of times each philosopher should eat: ");
    scanf("%d", &numTimesEat);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Simulate dining philosophers\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                simulateDining(numPhilosophers, numTimesEat);
                break;
            case 2:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

