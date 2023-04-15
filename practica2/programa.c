#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "$ "

int main() {
    char input[256];
    int status;
    pid_t pid;

    while (1) {
        printf(PROMPT);
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = 0; // Elimina el salto de línea del final

        if (strcmp(input, "EXIT") == 0) {
            break;
        }

        pid = fork();

        if (pid == -1) {
            perror("Error al crear el proceso");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execl(input, input, NULL) == -1) {
                perror("Error al ejecutar el archivo");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(&status);

            if (!WIFEXITED(status)) {
                printf("El proceso hijo no terminó correctamente\n");
            } else if (WEXITSTATUS(status) != 0) {
                printf("El archivo ejecutable no se pudo ejecutar correctamente\n");
            }
        }
    }

    return 0;
}