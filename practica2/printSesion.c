#include <stdio.h>
#include <unistd.h>

int main() {
    printf("La ID de la sesión del proceso es: %d\n", getsid(0));
    return 0;
}
