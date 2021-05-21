#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct list_node {
    list_elem elem;
    struct list_node *next;
} node;

list list_empty() {
    return NULL;
}

list list_addl(list_elem e, list l) {
    node *p;
    p = malloc(16);
    p->elem = e;
    p->next = l;
    l = p;

    return l;
}

bool list_is_empty(list l) {
    return l == NULL;
}

list_elem list_head(list l) {
    assert(!list_is_empty(l));
    return l->elem;
}

list list_tail(list l) {
    assert(!list_is_empty(l));
    node *p;
    p = l;
    l = l->next;
    free(p);

    return l;
}

list list_addr(list_elem e, list l) {
    node *p, *q;
    q = malloc(16);
    q->elem = e;
    q->next = NULL;
    if (!list_is_empty(l)) {
        p = l;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = q;
    } else {
        l = q;
    }

    return l;
}

unsigned int list_length(list l) {
    node *p;
    unsigned int n = 0;
    p = l;
    while (p != NULL) {
        n = n + 1u;
        p = p->next;
    }
    
    return n;
}

list list_concat(list l1, list l2) {
    node *p;
    p = l1;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = l2;

    return l1;
}

list_elem list_index(list l, unsigned int n) {
    assert(list_length(l) < n);
    node *p = l;
    unsigned int index = n;
    while (index > 0) {
        p = p->next;
        index = index - 1u;
    }

    return p->elem;
}

list list_take(list l, unsigned int n) {
    node *p;
    unsigned int index = n;
    p = l;
    while (n > 0 && p->next != NULL) {
        p = p->next;
        index = index - 1u;
    }
    while (p->next != NULL) {
        p = list_tail(p);
    }

    return l;
}

list list_drop(list l, unsigned int n) {
    node *p;
    unsigned int i = 0u;
    while (i < n && l != NULL) {
        p = l;
        l = p->next;
        free(p);
        i = i + 1u;
    }
    return l;
}

list copy_list(list l1) {
    list l2 = list_empty();
    node *p;
    p = l1;
    for(unsigned int i = 0u; i < list_length(l1); ++i) {
        l2 = list_addr(p->elem, l2);
        p = p->next;
    }

    return l2;
}

list list_destroy(list l) {
    return list_drop(l, list_length(l));
}
