#include <stdlib.h>
#include <stdio.h>
#include "currency.h"
#include "amount.h"

/**
 * Crea una tabla de tamaño fila * columna.
 * Tiene forma de arreglo unidimensional,
 * así que hay que usar g_index para buscar elementos en ella.
*/
static amount_t *crear_tabla(unsigned int filas, unsigned int columnas) {
    amount_t *tabla;
    tabla = calloc(filas * columnas, sizeof(amount_t));
    return tabla;
}
/**
 * Libera la memoria utilizada por la tabla dinámica.
*/
static amount_t *destroy_tabla(amount_t * tabla) {
    free(tabla);
    tabla = NULL;
    return tabla;
}

/**
 *  Devuelve el índice correspondiente a [fila, columna]
 *  de un arreglo unidimensional de ancho columnas.
*/ 
static amount_t g_index(unsigned int fila, unsigned int columna, unsigned int ancho) {
    return fila * ancho + columna;
}

static amount_t min_amount(amount_t a1, amount_t a2) {
    amount_t res;
    if (amount_le(a2, a1)) {
        res = a2;
    } else {
        res = a1;
    }
    return res;
}

/** Change-Making Dynamic
@param charge    A given price money to pay with coins
@param coins     An array of coin denominations

@return The minimum amount of coins needed to pay the charge

*/
amount_t change_making_dyn(currency_t charge, coin_t *coins, unsigned int n_coins) {
    amount_t *tabla;
    amount_t res;
    // Crea una tabla con n_coins+1 filas y charge+1 columnas.
    tabla = crear_tabla(n_coins+1, charge+1);
    // Si no hay que pagar nada, no necesito ninguna moneda.
    for(unsigned int i = 0u; i <= n_coins; i++) {
        tabla[g_index(i, 0, charge+1)] = 0;
    }
    // Si no hay monedas, nunca puedo pagar ningun monto.
    for(unsigned int j = 1u; j <= charge; j++) {
        tabla[g_index(0, j, charge+1)] = amount_inf();
    }
    // Los casilleros que no son casos base.
    for(unsigned int i = 1u; i <= n_coins; i++) {
        for(unsigned int j = 1u; j <= charge; j++) {
            // Si la denominación es demasiado grande, no me sirve
            if(coins[i-1] > j) {
                tabla[g_index(i,j,charge+1)] = tabla[g_index(i-1,j,charge+1)];
            // Si la denominación es usable, la celda es el mínimo entre usar esa moneda o no.
            }else {
                tabla[g_index(i,j,charge+1)] = min_amount(tabla[g_index(i-1,j,charge+1)],
                                             amount_sum(1,tabla[g_index(i,j-coins[i-1],charge+1)]));
            }
        }
    }
    res = tabla[g_index(n_coins, charge, charge+1)];
    tabla = destroy_tabla(tabla);
    return res;
}
