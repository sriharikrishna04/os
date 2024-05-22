#include <stdio.h>
#include <unistd.h>

int read_count = 0;
int resource = 1;
int rmutex = 1;

void wait(int *sem) {
    while (*sem <= 0);
    (*sem)--;
}

void signal(int *sem) {
    (*sem)++;
}

void reader(int id) {
    wait(&rmutex);
    read_count++;
    if (read_count == 1) {
        wait(&resource);
    }
    signal(&rmutex);

    printf("Reader %d is reading.\n", id);
    sleep(1);

    wait(&rmutex);
    read_count--;
    if (read_count == 0) {
        signal(&resource);
    }
    signal(&rmutex);
}

void writer(int id) {
    wait(&resource);
    printf("Writer %d is writing.\n", id);
    sleep(2);
    signal(&resource);
}

int main() {
    int rid;
    int wid;
	printf("Enter the reader id :");
	scanf("%d",&rid);
	printf("Enter the writer id :");
	scanf("%d",&wid);
    while (1) {
        int choice;
        printf("Enter 1 for Reader, 2 for Writer, or any other key to exit: \n");
        scanf("%d", &choice);
        if (choice == 1) {
            reader(rid++);
        } else if (choice == 2) {
            writer(wid++);
        } else {
        	printf("Code Executed");
            break;
        }
    }
    return 0;
}
