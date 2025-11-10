#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

int main() {
    int filedes[2];
    pid_t pid;
    char string[MAX], line[MAX];
    int n;

    printf("Enter the string to be given to the parent: ");
    fflush(stdout); // safer than fflush(stdin)
    scanf("%s", string);

    // Create pipe
    if (pipe(filedes) < 0) {
        perror("Pipe creation failed");
        exit(1);
    }

    // Create child process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        close(filedes[0]); // close read end
        write(filedes[1], string, strlen(string) + 1);
        close(filedes[1]);
    } else {
        // Child process
        close(filedes[1]); // close write end
        n = read(filedes[0], line, MAX);
        line[n] = '\0';
        printf("\nData read by child is: %s\n", line);
        close(filedes[0]);
    }

    return 0;
}
