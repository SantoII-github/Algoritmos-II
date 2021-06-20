#include <stdlib.h>
#include <assert.h>
#include "item.h"
#include "knapsack.h"
#include "set.h"

struct _s_knap {
    set packed_items;
    weight_t capacity;
    weight_t current_weight;
    value_t current_value;
};

static bool invrep(knapsack k) {
    return k == NULL || k->current_weight <= k->capacity;
}

knapsack knapsack_empty(unsigned int capacity) {
    knapsack new;
    new = malloc(sizeof(struct _s_knap));
    new->packed_items = set_empty();
    new->capacity = capacity;
    new->current_weight = 0;
    new->current_value = 0;
    assert(invrep(new));
    return new;
}

knapsack knapsack_clone(knapsack k) {
    knapsack clone = knapsack_empty(k->capacity);
    clone->packed_items = set_clone(k->packed_items);
    clone->current_weight = k->current_weight;
    clone->current_value = k->current_value;
    assert(invrep(k) && invrep(clone) &&
           set_cardinal(k->packed_items) == set_cardinal(clone->packed_items) &&
           k->capacity == clone->capacity &&
           k->current_value == clone->current_value &&
           k->current_weight == clone->current_weight &&
           k != clone);
    return clone;
}

knapsack knapsack_pack(knapsack k, item_t item) {
    assert(invrep(k) && knapsack_can_hold(k, item));
    k->packed_items = set_add(k->packed_items, item);
    k->current_weight = k->current_weight + item_weight(item);
    k->current_value = k->current_value + item_value(item);
    assert(invrep(k));
    return k;
}

bool knapsack_greater_value(knapsack k1, knapsack k2) {
    assert(invrep(k1) && invrep(k2));
    return k1->current_value > k2->current_value;
}

bool knapsack_is_full(knapsack k) {
    assert(invrep(k));
    return k->current_weight == k->capacity;
}

bool knapsack_can_hold(knapsack k, item_t item) {
    assert(invrep(k));
    return k->current_weight + item_weight(item) <= k->capacity;
}

weight_t knapsack_capacity(knapsack k) {
    assert(invrep(k));
    return k->capacity;
}

weight_t knapsack_weight(knapsack k) {
    assert(invrep(k));
    return k->current_weight;
}

value_t knapsack_value(knapsack k) {
    assert(invrep(k));
    return k->current_value;
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
    k->packed_items = set_destroy(k->packed_items);
    k->packed_items = NULL;
    free(k);
    k = NULL;
    return k;
}

