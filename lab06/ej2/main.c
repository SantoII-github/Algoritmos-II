#include <stdio.h>
#include "string.h"

int main(void) {
    char *cadena1 ="test";
    printf("cadena1: %s\n", cadena1);
    char *cadena2 ="test2";
    printf("cadena2: %s\n", cadena2);
    string test1 = string_create(cadena1);
    string test2 = string_create(cadena2);
    printf("Length cadena1: %u\n", string_length(test1));
    printf("Length cadena2: %u\n", string_length(test2));
    printf("cadena1 < cadena1?: %d\n", string_less(test1, test1));
    printf("cadena1 < cadena2?: %d\n", string_less(test1, test2));
    printf("cadena1 == cadena1?: %d\n", string_eq(test1, test1));
    printf("cadena1 == cadena2?: %d\n", string_eq(test1, test2));
    test1 = string_destroy(test1);
    test2 = string_destroy(test2);
}