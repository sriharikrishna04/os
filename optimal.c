#include <stdio.h>
int i,j;
// Function to check if a page is present in a frame
int isPageInFrames(int frames[], int numOfFrames, int page) {
    for (i = 0; i < numOfFrames; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to find the optimal frame to replace
int findOptimalFrame(int frames[], int numOfFrames, int pages[], int numOfPages, int currentIndex) {
    int farthest = currentIndex;
    int frameIndex = -1;

    for ( i = 0; i < numOfFrames; i++) {
        int j;
        for (j = currentIndex; j < numOfPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    frameIndex = i;
                }
                break;
            }
        }
        // If the frame is not found in the future, we should replace this frame
        if (j == numOfPages) {
            return i;
        }
    }

    // If all frames will be used in the future, replace the one farthest in the future
    return (frameIndex == -1) ? 0 : frameIndex;
}

// Function to print the frames
void printFrames(int frames[], int numOfFrames) {
    for ( i = 0; i < numOfFrames; i++) {
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

    // Initializing frames array
    for ( i = 0; i < numOfFrames; i++) {
        frames[i] = -1;
    }

    // Getting the page reference string from the user
    printf("Enter the reference string: ");
    for ( i = 0; i < numOfPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Implementing Optimal Page Replacement Algorithm
    for ( i = 0; i < numOfPages; i++) {
        // If the page is not already in a frame
        if (!isPageInFrames(frames, numOfFrames, pages[i])) {
            // If there is an empty frame, use it
            int emptyFrameFound = 0;
            for ( j = 0; j < numOfFrames; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    emptyFrameFound = 1;
                    break;
                }
            }
            // If no empty frame is found, find the optimal frame to replace
            if (!emptyFrameFound) {
                int frameToReplace = findOptimalFrame(frames, numOfFrames, pages, numOfPages, i + 1);
                frames[frameToReplace] = pages[i];
            }
            pageFaults++;
        }

        // Printing current state of frames
        printf("Page %d: ", pages[i]);
        printFrames(frames, numOfFrames);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

