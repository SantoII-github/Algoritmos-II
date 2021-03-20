#include <stdio.h>


int input_int(void) {
    int temp;
    printf("Ingrese un entero.\n");
    scanf("%d", &temp);

    return temp;
}

void input_array(int array[], unsigned int array_size) {
    for (unsigned int i = 0; i < array_size; i++) {
        array[i] = input_int();
    }
}

void print_array(int array[], unsigned int array_size) {
    for (unsigned int i = 0; i < array_size; i++) {
        printf("array[%d] : %d\n", i, array[i]);
    }
}