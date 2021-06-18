#include <stdlib.h>
#include <assert.h>
#include "item.h"
#include "knapsack.h"
#include "set.h"

struct _s_knap {
    set packed_items;
    /*
     * TODO: COMPLETAR
     *
     */
};

static bool invrep(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
    return true;
}

knapsack knapsack_empty(unsigned int capacity) {
    /*
     * TODO: COMPLETAR
     *
     */
}

knapsack knapsack_clone(knapsack k) {
    /*
     * TODO: COMPLETAR
     *
     */
}

knapsack knapsack_pack(knapsack k, item_t item) {
    /*
     * TODO: COMPLETAR
     */
}

bool knapsack_greater_value(knapsack k1, knapsack k2) {
    /*
     * TODO: COMPLETAR
     */
}

bool knapsack_is_full(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
}

bool knapsack_can_hold(knapsack k, item_t item) {
    /*
     * TODO: COMPLETAR
     */
}

weight_t knapsack_capacity(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
}

weight_t knapsack_weight(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
}

value_t knapsack_value(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
}

void knapsack_dump(knapsack k) {
    weight_t capacity, remind;
    assert(invrep(k));
    capacity = knapsack_capacity(k);
    remind = capacity - knapsack_weight(k);
    printf("knapsack value   : $%u\n", knapsack_value(k));
    printf("knapsack capacity: %u\n", capacity);
    printf("knapsack remind  : %u\n", remind);
    printf("**** packed items ****\n");
    set_dump(k->packed_items);
}

knapsack knapsack_destroy(knapsack k) {
    /*
     * TODO: COMPLETAR
     */
}

