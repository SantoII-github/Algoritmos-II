/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"


bool goes_before(movie_t s1, movie_t s2) {
    bool res = s1.runtime <= s2.runtime;
    return res;
}

unsigned int array_sorted_until(movie_t movielist[], unsigned int size) {
    unsigned int index;
    for(index = 0; index < size-1; ++index) {
      if(!goes_before(movielist[index], movielist[index+1])) {
        break;
      }
    }
    return index;
}

