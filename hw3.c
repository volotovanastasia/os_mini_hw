//Разработать программу в которой родительский процесс вычисляет число Фибоначчи,
//а процесс-ребенок вычисляет значение факториала.
//В качестве исходного значения используется аргумент из командной строки.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return factorial(n - 1) * n;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }

    int n = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == -1) {
        printf("Failed to create child process.\n");
    } else if (pid == 0) {
        printf("Child process is %d with parent %d. Factorial(%d) equal to %d\n", (int)getpid(), (int)getppid(), n, factorial(n));
    } else {
        printf("Parent process is %d. Fibonacci(%d) equal to  %d\n", (int)getpid(), n, fibonacci(n));
    }
    return 0;
}
