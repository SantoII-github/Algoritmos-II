#include "assert.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define ARRAY_SIZE 10

struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

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

struct max_min_result compute_max_min(int array[], unsigned int length) {
    assert(length > 0);
    unsigned int i;
    struct max_min_result result = { array[0], array[0], 0, 0 };

    for (i = 1; i < length; i++) {
        if (result.max_value < array[i]) {
            result.max_value = array[i];
            result.max_position = i;
        }
        if (result.min_value > array[i]) {
            result.min_value = array[i];
            result.min_position = i;
        }
    }

    return result;
}

int main()
{
    int array[ARRAY_SIZE] = { 4, -1, 5, 8, 9, 0, 3, 6, 0, 0 };

    input_array(array, ARRAY_SIZE);

    struct max_min_result result = compute_max_min(array, ARRAY_SIZE);
    printf("Máximo: %d\n", result.max_value);
    printf("Posición del máximo: %u\n", result.max_position);
    printf("Mínimo: %d\n", result.min_value);
    printf("Posición del mínimo: %u\n", result.min_position);
    return 0;
}
