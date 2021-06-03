#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino {
    int top;
    int bottom;
};


/* auxiliary functions for dumping */

static char mark(bool b) {
    return b ? 'O' : ' ';
}

static void dump_num(int num) {
  printf("      | %c     %c |\n",
         mark(num > 1), mark(num > 3));
  printf("      | %c  %c  %c |\n",
         mark(num > 5), mark(num % 2 == 1), mark(num > 5));
  printf("      | %c     %c |\n",
         mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num) {
  printf(" --------------------- \n");
  printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
  printf( "| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

  printf(" |    %c    ", mark(num % 2 == 1));
  printf( "|    %c    |\n", mark(num % 2 == 1));

  printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
  printf( "| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
  printf(" --------------------- \n");
}

void dump(int num_up, int num_down) {
    /* Pretty dump function for cool visualization :) */
    if (num_up != num_down)  {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    } else {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p) {
    bool valid_domino=true;
    if(p != NULL) {
        valid_domino = ((0 <= p->top) && (p->top <= 6)) && 
                       ((0 <= p->bottom) && (p->bottom <= 6));
    }
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down) {
    domino p;
    p = malloc(sizeof(struct _s_domino));
    p->top = num_up;
    p->bottom = num_down;
    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p) {
    assert(invrep(p));
    bool is_double = false;
    is_double = p->top == p->bottom;
    assert(invrep(p));
    return is_double;
}

bool domino_eq(domino p1, domino p2) {
    assert(invrep(p1) && invrep(p2));
    bool equals=false;
    equals = (p1->top == p2->top && p1->bottom == p2->bottom) ||
             (p1->top == p2->bottom && p1->bottom == p2->top);
    assert(invrep(p1) && invrep(p2));
    return equals;
}

bool domino_matches(domino p_top, domino p_bottom) {
    assert(invrep(p_top) && invrep(p_bottom));
    bool is_match=false;
    assert(!domino_eq(p_top, p_bottom));
    is_match = p_top->bottom == p_bottom->top;
    assert(invrep(p_top) && invrep(p_bottom));
    return is_match;
}

domino domino_flip(domino p) {
    assert(invrep(p));
    int temp = p->top;
    p->top = p->bottom;
    p->bottom = temp;
    assert(invrep(p));
    return p;
}

void domino_dump(domino p) {
    assert(invrep(p));
    dump(p->top, p->bottom);
}

domino domino_destroy(domino p) {
    assert(invrep(p));
    free(p);
    p = NULL;
    assert(invrep(p));
    return p;
}
