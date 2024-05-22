#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid, (void*)0, 0);

    printf("Enter data to write to shared memory: ");
    fgets(str, 1024, stdin);  // Using fgets instead of gets for safety

    printf("Data written in memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    return 0;
}

-------------------------
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid, (void*)0, 0);

    printf("Data read from memory: %s\n", str);

    // detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}


