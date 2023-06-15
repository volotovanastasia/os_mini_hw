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

int receiver_pid;

void send(int bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    } else {
        kill(receiver_pid, SIGUSR2);
    }
}

int main(void) {
    int sender_pid = getpid(), num;
    printf("Sender pid = %d\n\n", sender_pid);

    printf("Enter receiver pid: ");
    scanf("%d", &receiver_pid);
    printf("Enter number: ");
    scanf("%d", &num);

    if (num >= 0) {
        send(0);
    } else {
        send(1);
    }

    int n = num;
    for (int i = 0; i < 32; ++i) {
        send(n & 1);
        n >>= 1;
        sleep(10);
    }

    printf("\nNumber: %d\n", num);

    return 0;
}