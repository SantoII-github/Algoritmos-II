#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool stack_invrep(stack s) {
    return s->size < s->capacity;
}

stack stack_empty() {
    stack s = malloc(sizeof(stack));
    s->elems = calloc(100, sizeof(stack_elem));
    s->size = 0;
    s->capacity = 100;

    assert(stack_invrep);
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(stack_invrep);

    if(s->size == s->capacity) {
        s->capacity = s->capacity * 2;
        s = realloc(s, s->capacity * sizeof(stack_elem));
    }

    s->elems[s->size] = e;
    s->size = s->size + 1;

    assert(stack_invrep);
    return s;
}

stack stack_pop(stack s) {
    assert(stack_invrep);

    s->size = s->size - 1;

    assert(stack_invrep);
    return s;
}

unsigned int stack_size(stack s) {
    assert(stack_invrep);
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(stack_invrep);
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s) {
    assert(stack_invrep);
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) {
    assert(stack_invrep);

    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    for(unsigned int i = 1u; i <= s->size; ++i) {
        array[i-1] = s->elems[s->size-i];
    }

    assert(stack_invrep);
    return array;
}

stack stack_destroy(stack s) {
    assert(stack_invrep);
    free(s->elems);
    free(s);
    return s;
}