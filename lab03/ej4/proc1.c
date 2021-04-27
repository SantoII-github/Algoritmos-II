#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0) {
        y = x;
    } else {
        y = -x;
    }
}

int main(void) {
    int a, res;
    res = 0;
    a = -98;
    absolute(a, res);
    printf("%d", res);
    return 0;
}

/**
 * El programa va a imprimir un 0 porque la variable y en absolute no mantiene su
 * valor fuera de la función.
 */
