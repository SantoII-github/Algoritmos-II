#include <stdbool.h>
#include "even.h"

bool is_even_sorted(int array[], unsigned int length) {
    bool res = true;
    for(unsigned int index = 0; 2*(index+1) < length; ++index) {
        if(array[2*index] > array[2*(index+1)]) {
            res = false;
        }
    }
    return res;
}
