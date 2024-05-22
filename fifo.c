#include <stdio.h>

void printFrames(int frames[], int numOfFrames) {
    for (int i = 0; i < numOfFrames; i++) {
        if (frames[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int numOfFrames, numOfPages;

    // Getting the number of frames from the user
    printf("Enter the number of frames: ");
    scanf("%d", &numOfFrames);

    // Getting the number of pages in the reference string from the user
    printf("Enter the number of pages: ");
    scanf("%d", &numOfPages);

    int pages[numOfPages];
    int frames[numOfFrames];
    int pageFaults = 0;
    int index = 0;  // To keep track of the FIFO order

    // Initializing frames array
    for (int i = 0; i < numOfFrames; i++) {
        frames[i] = -1;
    }

    // Getting the page reference string from the user
    printf("Enter the reference string: ");
    for (int i = 0; i < numOfPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Implementing FIFO Page Replacement Algorithm
    for (int i = 0; i < numOfPages; i++) {
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < numOfFrames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If the page is not found in the frames, replace the oldest one
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % numOfFrames;  // Move to the next frame in FIFO order
            pageFaults++;
        }

        // Printing current state of frames
        printf("Page %d: ", pages[i]);
        printFrames(frames, numOfFrames);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

