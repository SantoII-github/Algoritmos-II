#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"

static type_elem set_min_pos(cost_t *D, set C, unsigned int n) {
    type_elem res = set_get(C);
    cost_t current = D[0];
    cost_t min = cost_inf();
    for(unsigned int i = 0u; i < n; i++) {
        current = D[i];
        if (cost_lt(current, min) && set_member(i, C)) {
            min = current;
            res = i;
        }
    }
    return res;
}

static cost_t min_cost(cost_t c1, cost_t c2) {
    cost_t res = c1;
    if(cost_lt(c2, c1)) {
        res = c2;
    }
    return res;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
    unsigned int c = 0u;
    unsigned int n = graph_max_vertexs(graph);
    cost_t * D = calloc(n, sizeof(cost_t));
    set C = set_empty();
    for(unsigned int i = 0u; i < n; i++) {
        C = set_add(C,i);
    }
    C = set_elim(C, init);
    for(unsigned int j = 0u; j < n; j++) {
        D[j] = graph_get_cost(graph, init, j);
    }
    while(! set_is_empty(C)) {
        c = set_min_pos(D, C, n);
        C = set_elim(C, c);
        for(unsigned int j = 0u; j < n; j++) {
            if(set_member(j,C)) {
                D[j] = min_cost(D[j], cost_sum(D[c], graph_get_cost(graph, c, j)));
            }
        }
    }
    C = set_destroy(C);

    return D;
}
