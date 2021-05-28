#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool check_greater(key_t e, dict_t d) {
    bool greater = true;
    if (d != NULL) {
        greater = key_less(d->key, e) && check_greater(e, d->left)
                                      && check_greater(e, d->right);
    }
    return greater;
}

static bool check_smaller(key_t e, dict_t d) {
    bool smaller = true;
    if (d != NULL) {
        smaller = key_less(e, d->key) && check_smaller(e, d->left)
                                      && check_smaller(e, d->right);
    }
    return smaller;
}

static bool invrep(dict_t d) {
    bool res = true;
    if (d != NULL) {
        res = check_greater(d->key, d->left) &&
              check_smaller(d->key, d->right) &&
              invrep(d->left) && invrep(d->right);
    }
    return res;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;

    assert(invrep(dict) && dict_length(dict)==0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    // Si llego a un dict vacío, creo el nodo y lo completo
    if (dict == NULL) {
        dict = malloc(sizeof(struct _node_t));
        dict->left = NULL;
        dict->right = NULL;
        dict->key = word;
        dict->value = def;
    }else{
        // Si la key es menor a la del dict, hago recursión por izq
        if(key_less(word, dict->key)) {
            dict->left = dict_add(dict->left, word, def);
        // Si la key es mayor a la del dict, hago recursión por der
        }else if(key_less(dict->key, word)) {
            dict->right = dict_add(dict->right, word, def);
        // Si la key es igual a la del dict, reemplazo la definición
        }else if(key_eq(dict->key, word)) {
            dict->value = def;
        }
    }

    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def = NULL;
    assert(invrep(dict));
    // Si el dict no es vacío
    if (dict != NULL) {
        // y encuentro la key, devuelvo su definición
        if (key_eq(dict->key, word)) {
            def = dict->value;
        // y word < key, hago recursión por izq
        }else if(key_less(word, dict->key)) {
            def = dict_search(dict->left, word);
        // y word > key, hago recursión por der
        }else if(key_less(dict->key, word)) {
            def = dict_search(dict->right, word);
        }
    }

    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool res = false;
    assert(invrep(dict));
    // Si el dict no es vacío
    if (dict != NULL) {
        // y encuentro la key, devuelvo true
        if (key_eq(dict->key, word)) {
            res = true;
        // y word < key, hago recursión por izq
        }else if(key_less(word, dict->key)) {
            res = dict_exists(dict->left, word);
        // y word > key, hago recursión por der
        }else if(key_less(dict->key, word)) {
            res = dict_exists(dict->right, word);
        }
    }

    assert(invrep(dict));
    return res;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    assert(invrep(dict));
    // Si dict no es NULL, sumo 1 a length y reviso sus subdicts.
    // Si dict es NULL, devuelvo 0
    if (dict != NULL) {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }

    return length;
}

static dict_t minValueNode(dict_t dict) {
    dict_t current = dict;

    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    if (dict != NULL) {
        if(key_less(word, dict->key)) {
            dict->left = dict_remove(dict->left, word);
        }else if(key_less(dict->key, word)) {
            dict->right = dict_remove(dict->right, word);
        }else if(key_eq(dict->key, word)) {
            // Nodo hoja o sólo con abb derecho
            if(dict->left == NULL) {
                dict_t temp = dict;
                dict = dict->right;
                free(temp);
            // Nodo con solo abb izquierdo
            }else if(dict->right == NULL) {
                dict_t temp = dict;
                dict = dict->left;
                free(temp);
            // Nodo con dos hijos
            }else {
                dict_t temp = minValueNode(dict->right);
                dict->key = temp->key;
                dict->right = dict_remove(dict->right, temp->key);
            }
        }
    }

    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));

    if(dict != NULL) {
        dict->right = dict_destroy(dict->right);
        dict->left = dict_destroy(dict->left);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }
    
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);

    if (dict != NULL) {
        // Llamada recursiva para el dict izq
        dict_dump(dict->left, file);
        // Imprimir key y value
        key_dump(dict->key, file);
        fprintf(file, ":");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        // Llamada recursiva para el dict der
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));

    if(dict != NULL) {
        dict->right = dict_destroy(dict->right);
        dict->left = dict_destroy(dict->left);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }

    assert(dict == NULL);
    return dict;
}
