#include <stdio.h>
#include <unistd.h>

int main() {
    printf("El ID del proceso padre es: %d\n", getppid());
    return 0;
}
