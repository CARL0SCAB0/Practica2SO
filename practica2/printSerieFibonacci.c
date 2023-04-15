#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Error al crear la tubería\n");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
    } else if (pid == 0) {
        /* Proceso hijo */
        close(fd[0]);  /* Cierra el descriptor de lectura de la tubería */
        int n;
        printf("Introduce el valor de n: ");
        scanf("%d", &n);
        write(fd[1], &n, sizeof(int)); /* Escribe el valor de n en la tubería */
        close(fd[1]); /* Cierra el descriptor de escritura de la tubería */
        execl("./fibonacci", "fibonacci", NULL); /* Ejecuta el programa que calcula el número de Fibonacci */
    } else {
        /* Proceso padre */
        close(fd[1]);  /* Cierra el descriptor de escritura de la tubería */
        int n;
        read(fd[0], &n, sizeof(int)); /* Lee el valor de n desde la tubería */
        wait(NULL); /* Espera a que el proceso hijo termine */
        printf("El elemento %d de la serie fibonacci es %d\n", n, fibonacci(n));
    }

    return 0;
}
