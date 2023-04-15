#include <stdio.h>
#include <unistd.h>

int main() {
    printf("El usuario que ejecutó el proceso es: %s\n", getlogin());
    return 0;
}
