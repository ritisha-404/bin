#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];             // pipefd[0] → read end, pipefd[1] → write end
    pid_t pid;
    char message[] = "Hello from Parent!";
    char buffer[100];

    // Step 1: Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Create a child process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // ---------- CHILD PROCESS ----------
        close(pipefd[1]);  // Close the unused write end

        // Step 3: Read message from pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);

        close(pipefd[0]);  // Close the read end after use
        exit(EXIT_SUCCESS);
    } 
    else {
        // ---------- PARENT PROCESS ----------
        close(pipefd[0]);  // Close the unused read end

        // Step 4: Write message to pipe
        write(pipefd[1], message, strlen(message) + 1);  // +1 for '\0'
        close(pipefd[1]);  // Close the write end after writing

        // Step 5: Wait for child process to terminate
        int status;
        wait(&status);

        // Step 6: Print child's exit status
        printf("Parent collected child exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
