#include <stdio.h>


int input_int(void) {
    int temp;
    printf("Ingrese un entero.\n");
    scanf("%d", &temp);

    return temp;
}

unsigned int input_unsigned_int(void) {
    unsigned int temp;
    printf("Ingrese un entero positivo.\n");
    scanf("%u", &temp);

    return temp;
}

void input_array(int array[], unsigned int array_size) {
    for (unsigned int i = 0; i < array_size; i++) {
        array[i] = input_int();
    }
}

void print_array(int array[], unsigned int array_size) { //Usar array_dump
    for (unsigned int i = 0; i < array_size; i++) {
        printf("array[%d] : %d\n", i, array[i]);
    }
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    
    if (length != 0){
        for(unsigned int index = 0; index < length-1; ++index) {
            printf("%d, ", a[index]);
        }
        printf("%d", a[length-1]);
    }

    printf("]\n");
}