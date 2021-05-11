#include <stdio.h>

typedef int list_elem;

typedef struct list_node {
    list_elem elem;
    struct list_node *next;
} node;

typedef struct list_node * list;

int main(void) {
    printf("%lu", (unsigned long)sizeof(list));
    return 0;
}