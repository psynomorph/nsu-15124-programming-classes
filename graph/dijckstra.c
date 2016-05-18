# include <stdlib.h>
# include <stdio.h>
# include "graphs.h"

GRAPH* read_graph(FILE* in) {
    GRAPH *g;
    int i, n;
    fscanf(in, "%i", &n);
    g = graph_create(n, GRAPH_DERICTED);
    while (!feof(in)) {
        int v1, v2, w;
        fscanf(in, "%i %i %i", &v1, &v2, &w);
        graph_set_link(g, v1, v2, w);
    }
    return g;
}

int get_min(int* v, int* d, int n) {
    int index = -1, min = GRAPH_INF_WEIGHT + 1;
    for (int i = 0; i < n; i++) {
        if (d[i] < min && !v[i]) {
            min = d[i];
            index = i;
        }
    }
    return index;
}

int* dijckstra(GRAPH* g, int sv) {
    int k, j, i, n = graph_count_of_vertices(g);
    int *v = (int*) malloc(sizeof(int) * n);
    int *d = (int*) malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        *(d + i) = i == sv ? 0 : GRAPH_INF_WEIGHT;
        *(v + i) = 0;
    }
    k = sv;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            if (i == k || v[i]) continue;
            int t = d[k] + graph_get_link(g, k, i);
            if (t < d[i]) d[i] = t;
        }
        v[k] = 1;
        k = get_min(v, d, n);
    }
    free(v);
    return d;
}

int main() {
    FILE* fin = fopen("graph.txt", "r");
    if (!fin) return -1;
    GRAPH* g = read_graph(fin);
    fclose(fin);
    int* d = dijckstra(g, 0);
    for (int i = 0; i < graph_count_of_vertices(g); i++) {
        printf("%i ", d[i]);
    }
    printf("\n");
    free(d);
    graph_delete(g);
    return 0;
}
