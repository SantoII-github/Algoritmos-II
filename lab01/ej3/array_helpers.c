#include "array_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    FILE *fptr;
    fptr = fopen(filepath, "r");
    if (fptr == NULL) {
        printf("Error opening file. Check if there are any typos in the filepath provided.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int array_size;
    fscanf(fptr, "%u", &array_size);
    if (array_size > max_size) {
        printf("This file's array size is higher than the maximum allowed.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int index = 0; index < array_size; ++index) { 
        fscanf(fptr, "%d", &array[index]); 
    }
    
    fclose(fptr); 

    return array_size;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    
    if (length != 0){
        for(unsigned int index = 0; index < length-2; ++index) {
            printf("%d, ", a[index]);
        }
        printf("%d", a[length-1]);
    }

    printf("]\n");
}