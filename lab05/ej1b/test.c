#include <stdio.h>
#include "stack.h"

int main(void) {
    /* Archivo para probar edge cases del TAD Stack */
    stack s = stack_empty();
    s = stack_push(s, 19);
    s = stack_pop(s);
    s = stack_push(s, 4);
    s = stack_pop(s);
    stack_elem *a = stack_to_array(s);
    printf("%d\n", a==NULL);
    s = stack_push(s, 1);
    s = stack_push(s, 2);
    s = stack_push(s, 3);
    s = stack_push(s, 4);
    s = stack_push(s, 5);
    a = stack_to_array(s);
    for(unsigned int i = 0u; i < 5u; ++i) {
        printf("%d", a[i]);
    }
    return 0;
}