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

int input_int(void) {
    int temp;
    printf("Input an integer.\n");
    scanf("%d", &temp);

    return temp;
}

void input_array(int array[], unsigned int array_size) {
    for (unsigned int i = 0; i < array_size; i++) {
        array[i] = input_int();
    }
}



int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    unsigned int length;
    
    printf("Input how many elements your array contains.\n");
    scanf("%u", &length);
    input_array(array, length);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return (EXIT_SUCCESS);
}