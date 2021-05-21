#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool stack_invrep(stack s) {
    bool res = true;

    if(s != NULL) {
        res = s->size <= s->capacity;
    }

    return res;
}

stack stack_empty() {
    stack s = NULL;
    assert(stack_invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(stack_invrep(s));

    if(s == NULL) {
        s = malloc(sizeof(struct _s_stack));
        s->elems = calloc(2, sizeof(stack_elem));
        s->capacity = 2;
        s->size = 0;
    }
    if(s->size == s->capacity) {
        s->capacity = s->capacity * 2;
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
    }
    s->elems[s->size] = e;
    s->size = s->size + 1;

    assert(stack_invrep(s));
    return s;
}

stack stack_pop(stack s) {
    assert(stack_invrep(s) && s != NULL);

    s->size = s->size - 1;

    assert(stack_invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(stack_invrep(s));

    unsigned int size;
    if(s == NULL) {
        size = 0;
    }else{
        size = s->size;
    }

    return size;
}

stack_elem stack_top(stack s) {
    assert(stack_invrep(s) && s != NULL);
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s) {
    assert(stack_invrep(s));
    return s == NULL || s->size == 0;
}

stack_elem *stack_to_array(stack s) {
    assert(stack_invrep(s));
    
    stack_elem *array;
    if(stack_is_empty(s)) {
        array = NULL;
    }else{
        array = calloc(stack_size(s), sizeof(stack_elem));
        for(unsigned int i = 0u; i < s->size; ++i) {
            array[i] = s->elems[i];
        }
    }

    assert(stack_invrep(s));
    return array;
}

stack stack_destroy(stack s) {
    assert(stack_invrep(s));

    if(s != NULL) {
        free(s->elems);
        free(s);
    }
    s = NULL;

    assert(stack_invrep(s));
    return s;
}