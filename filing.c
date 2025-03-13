#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Reversing file content
int main() {
    int srcfd, destfd;
    char buffer[100];

    // Opening source file for reading
    srcfd = open("src.txt", O_RDONLY);
    if (srcfd < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Reading from file
    int bytesread = read(srcfd, buffer, sizeof(buffer) - 1);
    if (bytesread < 0) {
        perror("Error reading file");
        close(srcfd);
        return 1;
    }

    if (bytesread == 0) {
        printf("File is empty\n");
        close(srcfd);
        return 1;
    }

    close(srcfd);

    // Null-terminate the buffer
    buffer[bytesread] = '\0';

    // Reverse content
    for (int i = 0, j = bytesread - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    // Opening/creating/truncating destination file
    destfd = open("dest.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destfd < 0) {
        perror("Error opening destination file");
        return 1;
    }

    // Writing to file
    int writebytes = write(destfd, buffer, bytesread);
    if (writebytes < 0) {
        perror("Error writing file");
        close(destfd);
        return 1;
    }

    close(destfd);
    printf("Successful reversing\n");

    return 0;
}


	

