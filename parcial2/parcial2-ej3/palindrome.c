#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "helpers/stack.h"
#include "helpers/queue.h"

static void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <phrase-to-check>\n\n"
           "Check if the phrase is a palindrome. Discards blank spaces from the "
           "given phrase when analysis is performed.\n",
           program_name);
}

static char* parse_phrase(int argc, char *argv[]) {
    /* Parse the phrase given by command line argument. */
    char *result=NULL;
    /* Program takes exactly one argument */
    if (argc != 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Use the first argument as the phrase */
    result = argv[1];
    /* return phrase */
    return result;
}

static size_t letter_count(char *str) {
    assert(str!=NULL);
    size_t count=0, i=0;
    while (str[i] != '\0') {
        // Increments only if str[i] is not blank
        count += str[i] != ' ';
        i++;
    }
    return count;
}

static char *remove_blanks(char *str, size_t *no_blanks_count) {
    assert(str!=NULL);
    size_t size_noblank=0;
    size_t count=0,i=0;
    char *no_blank=NULL;
    // Get the length of the phrase without blanks
    size_noblank = letter_count(str);
    // Asign memory to no_blank to save the phrase without spaces, +1 for '\0'
    no_blank = calloc(size_noblank+1, sizeof(char));
    // Advance over str, if the character isn't a blank, copy it to no_blank
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            no_blank[count] = str[i];
            count++;
        }
        i++;
    }
    // Save in *no_blanks_count the size of str without blanks
    *no_blanks_count = size_noblank;
    return no_blank;
}

int main(int argc, char *argv[]) {
    // First parameter is used as phrase
    char *phrase=argv[1];
    //
    stack letters_lifo;
    bool is_palindrome=true;
    size_t i=0;
    // Parse arguments and get the phrase to be analysed
    phrase=parse_phrase(argc, argv);
    // Discard blank spaces
    queue letters_fifo;
    // Create an empty queue
    letters_fifo = queue_empty();
    // Make a copy of the phrase without the blank characters
    char *phrase_noblank = NULL;
    size_t size_without_blanks;
    phrase_noblank = remove_blanks(phrase, &size_without_blanks);
    // Add non-blank characters to queue
    while(phrase_noblank[i] != '\0') {
        letters_fifo = queue_enqueue(letters_fifo, phrase_noblank[i]);
        i++;
    }
    // A stack (lifo) needed for checking algorithm
    letters_lifo=stack_empty();
    // Save half phrase in the stack
    size_t size_noblank = queue_size(letters_fifo);
    size_t half_size=size_noblank / 2;
    while (stack_size(letters_lifo) != half_size) {
        queue_elem letter;
        // Save in letter the first element of the queue then dequeue it
        letter = queue_first(letters_fifo);
        letters_fifo = queue_dequeue(letters_fifo);
        letters_lifo = stack_push(letters_lifo, letter);
    }
    if (size_noblank % 2 == 1) {
        letters_fifo = queue_dequeue(letters_fifo);
    }
    // For each letter in the stack must be one in the queue
    assert(queue_size(letters_fifo)==stack_size(letters_lifo));
    // Simetry check
    while (!stack_is_empty(letters_lifo)) {
        bool match_letter=false;
        match_letter = stack_top(letters_lifo) == queue_first(letters_fifo);
        is_palindrome = is_palindrome && match_letter;
        letters_lifo = stack_pop(letters_lifo);
        letters_fifo = queue_dequeue(letters_fifo);
    }
    // Check emptyness simetry
    assert(queue_is_empty(letters_fifo));
    // Destroy instances
    letters_lifo = stack_destroy(letters_lifo);
    letters_fifo = queue_destroy(letters_fifo);
    free(phrase_noblank);

    printf(is_palindrome ? "es palíndromo!\n": "no es palíndromo\n");
    return 0;
}
