#include "array_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    FILE *fptr; //Creo una variable para guardar el archivo.
    fptr = fopen(filepath, "r"); //Abro el archivo con el filepath que recibe la funcion.
    if (fptr == NULL) {            //Salgo del programa si hay un error abriendo el archivo.
        printf("Error opening file. Check if there are any typos in the filepath provided.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int array_size;
    fscanf(fptr, "%u", &array_size); //Leo el primer entero y lo guardo en la variable array_size. El puntero queda en el primer caracter newline.
    if (array_size > max_size) {     //Si el tamaño del arreglo es mayor al permitido, salgo del programa.
        printf("This file's array size is higher than the maximum allowed.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int index = 0; index < array_size; ++index) { //El ciclo recorre los enteros de la segunda linea del archivo hasta la posicion dada por el primer entero de longitud. 
        fscanf(fptr, "%d", &array[index]); //Por cada index, asigna el entero que corresponde en el archivo a la posicion en el array dado en los parametros.
    }
    
    fclose(fptr); //Cierro el archivo.

    return array_size; //devuelve el tamaño del array para usarlo en main.
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    
    if (length != 0){ //Si la longitud del arreglo es distinta de 0 imprime cada elemento del arreglo.
        for(unsigned int index = 0; index < length-1; ++index) {
            printf("%d, ", a[index]);
        }
        printf("%d", a[length-1]);
    }

    printf("]\n");
}

bool array_is_sorted(int a[],unsigned int max_size) {
    bool result = true;
    for (unsigned int index = 0; index < max_size - 1 && result; ++index) {
        if (a[index] > a[index+1]) {
            result = false;
        }
    }

    return result;
}

void array_swap(int a[], unsigned int i, unsigned int j) {
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void invert_array(int array[], unsigned int max_size) {
    unsigned int halfway_point = max_size / 2;
    unsigned int max_index = max_size -1;

    for (unsigned int index = 0; index < halfway_point; ++index) {
        array_swap(array, index, max_index - index);
    }
}