// Разработать программы клиента и сервера, взаимодействующих через разделяемую память с использованием функций POSIX.
// Клиент генерирует случайные числа в том же диапазоне, что и ранее рассмотренный на семинаре пример.
// Сервер осуществляет их вывод.
//
// Необходимо обеспечить корректное завершение работы для одного клиента и сервера, при котором удаляется сегмент
// разделяемой памяти и завершается работа обеих программ независимо от того, какая из них инициировала завершение.
//
// Предложить и реализовать свой вариант корректного завершения. Описать этот вариант в отчете.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define SHM_SIZE 1024

int *shm_ptr;

void signal_handler(int signal) {
    if (signal == SIGINT) {
        *shm_ptr = -1;
        printf("Server: Termination signal received. Exiting...\n");
    }
}

int main() {
    int shm_fd;
    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    shm_ptr = (int *) mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    signal(SIGINT, signal_handler);

    printf("Server: Waiting for client...\n");
    while (*shm_ptr != -1) {
        printf("Server: Received number: %d\n", *shm_ptr);
        shm_ptr++;
    }

    if (munmap(shm_ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }

    if (close(shm_fd) == -1) {
        perror("close");
        exit(1);
    }

    if (shm_unlink("/myshm") == -1) {
        perror("shm_unlink");
        exit(1);
    }

    printf("Server: Exiting.\n");

    return 0;
}