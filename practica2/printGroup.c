#include <stdio.h>
#include <unistd.h>

int main() {
    printf("El ID del grupo del proceso es: %d\n", getpgrp());
    return 0;
}
