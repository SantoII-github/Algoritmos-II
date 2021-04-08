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

unsigned int array_from_input(int array[], unsigned int max_size) {
    unsigned int length;
    printf("Input your array's length\n");
    scanf("%u", &length);
    
    printf("Input your array's elements\n");
    for (unsigned int i = 0; i < length && i < max_size; ++i) {
        scanf("%d", &array[i]);
    }

    return length;
}

int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_input(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return (EXIT_SUCCESS);
}