#include "sorted.h"

unsigned int sorted_until(int array[], unsigned int size) {
    unsigned int index;
    for(index = 0; index < size-1; ++index) {
        if (array[index] > array[index+1]) {
            break;
        }
    }
    return index;
}
