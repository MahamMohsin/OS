#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Correct usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    int pipefd[2]; // Pipe for communication
    if (pipe(pipefd) < 0) {
        perror("Pipe creation failed");
        return 1;
    }

    int pid = fork(); // Create child process
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process: reads from file and writes to pipe
        close(pipefd[0]); // Close read end

        int inputfd = open(argv[1], O_RDONLY);
        if (inputfd == -1) {
            perror("Error opening input file");
            return 1;
        }

        char ch;
        while (read(inputfd, &ch, 1) > 0) {
            write(pipefd[1], &ch, 1);
        }

        close(inputfd);
        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for child to finish
        return 0;
    }

    if (pid == 0) {  // Child process: reads from pipe and writes to output file
        close(pipefd[1]); // Close write end

        int outputfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputfd == -1) {
            perror("Error opening output file");
            return 1;
        }

        char ch;
        while (read(pipefd[0], &ch, 1) > 0) {
            write(outputfd, &ch, 1);
        }

        close(outputfd);
        close(pipefd[0]); // Close read end
        return 0;
    }

    return 0;
}

	

