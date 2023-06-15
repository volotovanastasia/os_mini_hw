// Разработать программы клиента и сервера, взаимодействующих через разделяемую память
// с использованием функций UNIX SYSTEM V. Клиент генерирует случайные числа в том же диапазоне,
// что и ранее рассмотренный на семинаре пример. Сервер осуществляет их вывод.
//
// Необходимо обеспечить корректное завершение работы для одного клиента и сервера, при котором удаляется
// сегмент разделяемой памяти и завершается работа обеих программ независимо от того,
// какая из них инициировала завершение.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define MAX_VALUE 999

int *shm_ptr;

void signal_handler(int signal) {
    if (signal == SIGINT) {
        *shm_ptr = -1;
        printf("Client: Received termination signal. Exiting...\n");
    }
}

int main() {
    int shmid;

    shmid = shmget(0x2FF, SHM_SIZE, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    signal(SIGINT, signal_handler); // Установка обработчика сигнала завершения

    srand(time(NULL));
    printf("Client: Generating random numbers\n");
    *shm_ptr = rand() % (MAX_VALUE + 1);
    while (*shm_ptr != -1) {
        printf("Client: Generated number: %d\n", *shm_ptr);
        shm_ptr++;
        *shm_ptr = rand() % (MAX_VALUE + 1);
        sleep(1);
    }

    shmdt(shm_ptr);

    printf("Client: Exiting...\n");

    return 0;
}
