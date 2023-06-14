// Разработать программу, использующую для работы с текстовыми файлами системные вызовы.
// Программа на языке C должна прочитать, используя буфер, размер которого ПРЕВЫШАЕТ читаемые файлы
// и записать прочитанный файл в файл с другим именем.
// Имена файлов для чтения и записи задавать с использованием аргументов командной строки.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const int size = 128;

int main(int argc, char *argv[]) {
    char buffer[size];
    ssize_t read_bytes;

    if (argc != 3) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    char *input_file = argv[1];
    char *output_file = argv[2];

    int in_fd = open(input_file, O_RDONLY);
    if (in_fd == -1) {
        printf("Cannot open input file\n");
        return 1;
    }

    int out_fd = open(output_file, O_WRONLY | O_CREAT);
    if (out_fd == -1) {
        printf("Cannot open output file\n");
        return 1;
    }

    while ((read_bytes = read(in_fd, buffer, size)) > 0) {
        if (write(out_fd, buffer, read_bytes) != read_bytes) {
            printf("Writing to output file ended with error\n");
            return 1;
        }
    }
    if (read_bytes == -1) {
        printf("Reading input file ended with error\n");
        return 1;
    }

    if (close(in_fd) == -1) {
        printf("Cannot close input file\n");
        return 1;
    }
    if (close(out_fd) == -1) {
        printf("Cannot close output file\n");
        return 1;
    }
    return 0;
}

