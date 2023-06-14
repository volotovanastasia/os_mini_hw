// Разработать программы, реализующие двусторонний обмен данными по именованным каналам.
// То есть, организовать их взаимодействие как независимых процессов.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char message[BUFFER_SIZE];

    mkfifo(FIFO_NAME, 0666);

    printf("Receiver: waiting for sender...\n");

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    read(fd, message, sizeof(message));
    printf("Message: %s", message);

    close(fd);

    unlink(FIFO_NAME);

    return 0;
}