#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"
#define COUNT 5

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool check_greater(abb_elem e, abb tree) {
    bool greater = true;
    if (tree != NULL) {
        greater = elem_less(tree->elem, e) && check_greater(e, tree->left) 
                                           && check_greater(e, tree->right);
                        
    }
    return greater;
}

static bool check_smaller(abb_elem e, abb tree) {
    bool smaller = true;
    if (tree != NULL) {
        smaller = elem_less(e, tree->elem) && check_smaller(e, tree->left)
                                           && check_smaller(e, tree->right);
    }
    return smaller;
}

static bool invrep(abb tree) {
    bool res = true;
    if (tree != NULL) {
        res = check_greater(tree->elem, tree->left) &&
                check_smaller(tree->elem, tree->right) &&
                invrep(tree->left) && invrep(tree->right);
    }

    return res;
}

abb abb_empty(void) {
    abb tree;

    tree = NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    // Si llego a un árbol vacío, creo el nodo y lo completo
    if (tree == NULL) {
        tree = malloc(sizeof(struct _s_abb));
        tree->left = NULL;
        tree->elem = e;
        tree->right = NULL;
    }else{
        // Si el elemento es menor al del árbol, hago recursión en el árbol izq
        if(elem_less(e, tree->elem)) {
            tree->left = abb_add(tree->left, e);
        // Si el elemento es mayor al del árbol, hago recursión en el árbol der
        }else if(elem_less(tree->elem, e)){
            tree->right = abb_add(tree->right, e);
        // Si el elemento no es mayor ni menor, es igual, no hago nada
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}


bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if(tree != NULL) {
        // Si encuentro e, existe.
        if(elem_eq(tree->elem, e)) {
            exists = true;
        // Si e es más chico que tree->elem, busco en el abb izq
        }else if(elem_less(e, tree->elem)) {
            exists = abb_exists(tree->left, e);
        // Si e es más grande que tree->elem, busco en el abb der
        }else if(elem_less(tree->elem, e)) {
            exists = abb_exists(tree->right, e);
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree == NULL) {
        length = 0;
    }else{
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) ||  length > 0));
    return length;
}

static abb minValueNode(abb tree) {
    abb current = tree;

    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (tree != NULL) {
        if(elem_less(e, tree->elem)) {
            tree->left = abb_remove(tree->left, e);
        }else if(elem_less(tree->elem, e)) {
            tree->right = abb_remove(tree->right, e);
        }else if(elem_eq(tree->elem, e)) {
            // Nodo hoja o sólo con abb derecho
            if(tree->left == NULL) {
                abb temp = tree;
                tree = tree->right;
                free(temp);
            // Nodo con solo abb izquierdo
            }else if(tree->right == NULL) {
                abb temp = tree;
                tree = tree->left;
                free(temp);
            // Nodo con dos hijos
            }else {
                abb temp = minValueNode(tree->right);
                tree->elem = temp->elem;
                tree->right = abb_remove(tree->right, temp->elem);
            }
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    abb pointer = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(pointer->right != NULL) {
        pointer = pointer->right;
    }
    max_e = pointer->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    abb pointer = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (pointer->left != NULL) {
        pointer = pointer->left;
    }
    min_e = pointer->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

/*
Vieja abb_dump, cuyo ciclo imprime los elementos en orden de menor a mayor.
void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}
*/
static void abb_dump_rec(abb tree, int space) {
    // Caso base
    if (tree == NULL)
        return;
  
    // Incrementar espacio entre niveles
    space += COUNT;
  
    // Procesar primero el subárbol derecho
    abb_dump_rec(tree->right, space);
  
    // Imprimir el nodo actual tras los espacios correspondientes
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", tree->elem);
  
    // Procesar el subárbol izquierdo
    abb_dump_rec(tree->left, space);
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    abb_dump_rec(tree, 0);
}


abb abb_destroy(abb tree) {
    assert(invrep(tree));
    // Si tree es null no hago nada.
    // Si tree no es null, llamo a la función para sus subárboles y después libero la memoria.
    if(tree != NULL) {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

