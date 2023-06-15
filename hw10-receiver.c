// Побитовая передача целого числа от одного процесса другому с помощью сигналов SIGUSR1, SIGUSR2.
//
//Необходимо написать две программы — передатчик и приемник, которые будут запускаться с разных терминалов.
// Каждая программа вначале печатает свой PID и запрашивает ввод с клавиатуры PID программы–собеседника
// (вводится пользователем). Порядок ввода PID не имеет значения. Программа передатчик запрашивает с клавиатуры
// ввод целого десятичного числа (число может быть и отрицательным!). Введенное число побитово передается
// программе-приемнику с использованием пользовательских сигналов SIGUSR1 и SIGUSR2. Программа–приемник после
// завершения приема печатает принятое число в десятичной системе счисления.

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int received_bit;

void handler(int nsig) {
    if (nsig == SIGUSR1) {
        received_bit = 0;
    } else if (nsig == SIGUSR2) {
        received_bit = 1;
    }
}

int main(void) {
    (void) signal(SIGUSR1, handler);
    (void) signal(SIGUSR2, handler);

    int sender_pid, receiver_pid = getpid();
    printf("Receiver pid = %d\n\n", receiver_pid);

    printf("Enter sender pid: ");
    scanf("%d", &sender_pid);

    kill(sender_pid, SIGUSR1);

    int bits[32];
    for (int i = 0; i < 32; ++i) {
        sleep(10);
        bits[i] = received_bit;
        printf("%d", received_bit);
        kill(sender_pid, SIGUSR1);
    }

    int num = 0;
    for (int i = 0; i < 32; ++i) {
        num |= bits[i] << i;
    }

    printf("\nNumber: %d\n", num);

    return 0;
}