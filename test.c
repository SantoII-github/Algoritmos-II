#include <stdio.h>

struct _counter {
    unsigned int count;
};

typedef struct _counter * counter;

int main(void) {
    printf("%lu", (unsigned long)sizeof(counter));
    return 0;
}