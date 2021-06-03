#include <stdio.h>
#include "stack.h"

int main(void) {
    stack test=NULL;
    stack stack_empty();
    test = stack_push(test, 'a');
    printf("Push a\n");
    test = stack_push(test, 'b');
    printf("Push b\n");
    char temp = stack_top(test);
    printf("%c\n", temp);
    test = stack_pop(test);
    temp = stack_top(test);
    printf("%c\n", temp);
}