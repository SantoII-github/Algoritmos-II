/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return (EXIT_SUCCESS);
}