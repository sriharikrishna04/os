#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Function to reverse the string
void reverseString(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to check if the string is a palindrome
int isPalindrome(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[100];
    pid_t pid1, pid2;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // First child process
        reverseString(str);
        printf("Reversed string: %s\n", str);
        // Save the reversed string to a file for the second child to read
        FILE *file = fopen("reversed.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(1);
        }
        fprintf(file, "%s", str);
        fclose(file);
        exit(0);
    } else {
        // Wait for the first child to finish
        wait(NULL);

        pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            exit(1);
        } else if (pid2 == 0) {
            // Second child process
            // Read the reversed string from the file
            FILE *file = fopen("reversed.txt", "r");
            if (file == NULL) {
                perror("fopen");
                exit(1);
            }
            fgets(str, sizeof(str), file);
            fclose(file);

            if (isPalindrome(str)) {
                printf("The reversed string is a palindrome.\n");
            } else {
                printf("The reversed string is not a palindrome.\n");
            }
            // Remove the file after use
            remove("reversed.txt");
            exit(0);
        } else {
            // Wait for the second child to finish
            wait(NULL);
        }
    }

    return 0;
}


