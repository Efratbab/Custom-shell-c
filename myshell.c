#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHAR 1024
#define ARRAY_SIZE 100

// Array to save the history commands
char *historyArray[ARRAY_SIZE];

// Function to print the history array
void printHistory(int numOfHistory) {
    for (int i = 0; i < numOfHistory; i++) {
        printf("%s\n", historyArray[i]);
    }
}

int main(int argc, char *argv[]) {
    char input[MAX_CHAR];
    char *args[MAX_CHAR / 2 + 1];
    int i;
    char *string;
    int numOfHistory = 0;

    // Initialize newPath with the original PATH
    char *originalPath = getenv("PATH");
    char newPath[MAX_CHAR * 10];
    strcpy(newPath, originalPath);

    // Append the additional paths provided as arguments to the new PATH
    for (int j = 1; j < argc; j++) {
        strcat(newPath, ":");
        strcat(newPath, argv[j]);
    }

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Get input from user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            continue;
        }

        // Remove the newline character from the end of input if present
        input[strcspn(input, "\n")] = 0;

        // Parse the input into command and arguments
        i = 0;
        string = strtok(input, " ");
        while (string != NULL) {
            args[i++] = string;
            string = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Temporarily set the new PATH environment variable
        setenv("PATH", newPath, 1);

        // Implement "exit" command
        if (strcmp(args[0], "exit") == 0) {
            historyArray[numOfHistory] = strdup(input);
            break;
        }
        // Implement "history" command
        else if (strcmp(args[0], "history") == 0) {
            historyArray[numOfHistory] = strdup(input);
            printHistory(numOfHistory);
        }
        // Implement "cd" command
        else if (strcmp(args[0], "cd") == 0) {
            char cmd[MAX_CHAR];
            snprintf(cmd, sizeof(cmd), "cd %s", args[1]);
            historyArray[numOfHistory] = strdup(cmd);
            if (chdir(args[1]) != 0) {
                perror("chdir");
            }
        }
        // Implement "pwd" command
        else if (strcmp(args[0], "pwd") == 0) {
            historyArray[numOfHistory] = strdup(input);
            char cwd[MAX_CHAR];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd() error");
            }
        } else {
            // Save the command in history
            historyArray[numOfHistory] = strdup(input);
            pid_t pid = fork();
            if (pid == 0) {
                // Child process executes the command
                execvp(args[0], args);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // Parent process waits for the child to complete
                waitpid(pid, NULL, 0);
            } else {
                perror("fork failed");
            }
        }
        numOfHistory++;
    }

    // Free allocated memory
    for (int j = 0; j < numOfHistory; j++) {
        free(historyArray[j]);
    }

    // Restore the original PATH environment variable
    setenv("PATH", originalPath, 1);

    return 0;
}