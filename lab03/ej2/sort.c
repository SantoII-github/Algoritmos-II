/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y) {
    bool res = x.rank <= y.rank;
    return res;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int i, unsigned int j) {
    player_t temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/** 
 * @brief Permutes elements of a[izq..der] and returns pivot such that:
 * - izq <= pivot <= der
 * - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
 * - a[pivot] 'goes_before' all the elements in a(pivot,der]
 * 
 * @param[in] a Players array
 * @param lft Left index of segment to permute
 * @param rgt Right index of segment to permute
 */
static unsigned int partition(player_t a[], unsigned int lft, unsigned int rgt) {
    unsigned int i,j, ppiv;
    ppiv = lft;
    i = lft + 1;
    j = rgt;
    while (i <= j) {
        if (goes_before(a[i], a[ppiv])) {
            i = i + 1;
        }
        else if (goes_before(a[ppiv],a[j])) {
            j = j - 1;
        }
        else if (goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv])) {
            swap(a, i, j);
        }
    }
    swap(a, ppiv, j);
    ppiv = j;

    return ppiv;
}

/**
 * @brief Called by sort to use the quick sort algorithm
 * @param[in] a Players array
 * @param lft Left index of segment to sort
 * @param rgt Right index of segment to sort
 */
static void quick_sort_rec(player_t a[], unsigned int lft, unsigned int rgt) {
    unsigned int ppiv;
    if (rgt > lft) {
        ppiv = partition(a, lft, rgt);
        quick_sort_rec(a, lft, (ppiv == 0u) ? 0u : ppiv - 1u);
        quick_sort_rec(a, ppiv+1, rgt);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
