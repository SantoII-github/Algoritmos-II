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
    if (tree == NULL) {
        res = true;
    } else {
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

static abb_elem inorder_successor(abb tree) {
    abb pointer;
    abb_elem inorder_successor;
    // Empiezo en la rama derecha de donde encontré e, y me muevo a la izq lo max
    pointer = tree->right;
    while (pointer->left != NULL) {
        pointer = pointer->left;
    }
    inorder_successor = pointer->elem;
    free(pointer);

    return inorder_successor;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    // Si tree es vacío, no se ejecuta nada y devuelve NULL
    if(tree != NULL){
        // Si e < tree->elem, lo busco en abb left
        if(elem_less(e, tree->elem)) {
            tree = abb_remove(tree->left, e);
        // Si tree->elem < e, lo busco en abb right
        }else if(elem_less(tree->elem, e)) {
            tree = abb_remove(tree->right, e);
        // Si tree->elem = e, uso el algoritmo para eliminarlo
        }else if(elem_eq(tree->elem, e)) {
            // Si es una hoja lo borro directamente, si sólo tiene abb derecho lo reemplazo por su hijo
            if(tree->left == NULL) {
                tree = tree->right;
            // Si sólo tiene abb izq lo reemplazo por su hijo
            }else if(tree->right == NULL) {
                tree = tree->left;
            // Si tiene dos hojas, guardo el valor mínimo del abb der para reemplazar el nodo.
            }else{
                tree->elem = inorder_successor(tree);
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
void abb_dump_rec(abb tree, int space) {
    assert(invrep(tree));
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

