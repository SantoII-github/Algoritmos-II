#include <assert.h>
#include "change_making.h"
#include "amount.h"
#include "set.h"
#include "currency.h"

static amount_t min_amount(amount_t a1, amount_t a2) {
    amount_t res;
    if (amount_le(a2, a1)) {
        res = a2;
    } else {
        res = a1;
    }
    return res;
}

/** Change-Making Algorithm
@param charge    A given price money to pay with coins
@param coins     A set of coin denominations

@return The minimun amount of coins needed for paying the charge
*/
amount_t change_making(currency_t charge, set coins) {
    set_elem c;
    set C_aux;
    amount_t S;
    // Si no hay que pagar nada, no necesito monedas.
    if (charge == 0) {
        S = 0;
    // Si no hay monedas, nunca puedo pagar ningun monto.
    }else if (set_is_empty(coins)) {
        S = amount_inf();
    }else {
        // Elijo una moneda
        C_aux = set_clone(coins);
        c = set_get(coins);
        C_aux = set_elim(C_aux, c);
        // Si es usable, uso el mínimo entre usarla y no usarla
        if (c <= charge) {
            S = min_amount(amount_sum(1,change_making(charge-c, coins)), 
                                        change_making(charge, C_aux));
        // Si no es usable no la uso.
        }else {
            S = change_making(charge, C_aux);
        }
    set_destroy(C_aux);
    }
    return S;
}
