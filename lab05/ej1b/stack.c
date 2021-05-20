#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    unsigned int size;
    struct _s_stack *next;
};

stack stack_empty() {
    stack s= malloc(sizeof(stack));
    s->size = 0;
    return s;
}

stack stack_push(stack s, stack_elem e) {
    struct _s_stack *p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->size = s->size + 1;
    p->next = s;
    s = p;
    return s;
}

stack stack_pop(stack s) {
    stack p;
    p = s;
    s = s->next;
    s->size = p->size -1;
    free(p);
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s) {
    return s->size == 0;
}

stack_elem *stack_to_array(stack s) {
    stack_elem *a;
        if(stack_is_empty(s)){
        a = NULL;
    }else{
        stack p = s;
        a = calloc(stack_size(s), sizeof(stack_elem));
        for(unsigned int i = 1; i <= stack_size(s); ++i) {
            a[stack_size(s)-i] = p->elem;
            p = p->next;
        }
    }
    return a;
}

stack stack_destroy(stack s) {
    stack p;
    while (s != NULL) {
        p = s;
        s = s->next;
        free(p);
    }
    return s;
}