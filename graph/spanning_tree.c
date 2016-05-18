# include <stdlib.h>
# include <stdio.h>
# include "graphs.h"

typedef struct _edge {
    int vertex1;
    int vertex2;
    int weight;
} EDGE;

typedef struct _edge_vector {
    EDGE* edges;
    int count;
} EDGE_VECTOR;

int edge_cmp(const void* p1, const void* p2) {
    EDGE *e1 = (EDGE*) p1, *e2 = (EDGE*) p2;
    if (e1->weight != e2->weight)
        return - (e1->weight - e2->weight);
    else if (e1->vertex1 != e2->vertex1)
        return e1->vertex1 - e2->vertex1;
    else
        return e1->vertex2 - e2->vertex2;
}

void sort_edge_vector(EDGE_VECTOR v) {
    qsort(
        v.edges,
        v.count,
        sizeof(EDGE),
        edge_cmp
    );
}

GRAPH* read_graph(FILE* in) {
    GRAPH *g;
    int i, n;
    fscanf(in, "%i", &n);
    g = graph_create(n, GRAPH_UNDERICTED);
    while (!feof(in)) {
        int v1, v2, w;
        fscanf(in, "%i %i %i", &v1, &v2, &w);
        graph_set_link(g, v1, v2, w);
    }
    return g;
}


void print_graph(GRAPH* g, FILE* out) {
    int i, j, n = graph_count_of_vertices(g);
    fprintf(out, "%i\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (!graph_has_link(g, i, j)) continue;
            fprintf(out, "%i %i %i\n", i, j, graph_get_link(g, i, j));
        }
    }
}

EDGE_VECTOR get_edges(GRAPH* g) {
    EDGE_VECTOR v;
    int n = graph_count_of_vertices(g);
    v.edges = (EDGE*) malloc(sizeof(EDGE) * n * n / 2 + 1);
    int c = 0;
    for (int i =  1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (graph_has_link(g, i, j)) {
                EDGE e = {i, j, graph_get_link(g, i, j)};
                v.edges[c++] = e;
            }
        }
    }
    v.count = c;
    return v;
}

void _walk(GRAPH* g, int curr, int to, int* v) {
    v[curr] = 1;
    if (to == curr) return;
    for (int i = 0; i < graph_count_of_vertices(g); i++) {
        if (i == curr || v[i] || !graph_has_link(g, curr, i)) continue;
        _walk(g, i, to, v);
        if (v[to]) break;
    }
}

int has_way(GRAPH* g, int to) {
    int n = graph_count_of_vertices(g);
    int *v = (int*) malloc(sizeof(int) * n);

    for (int *i = v; i < v + n; i++) *i = 0;

    _walk(g, 0, to, v);

    int res = v[to];
    free(v);
    return res;
}

void build_spanning_tree(GRAPH* g) {
    EDGE_VECTOR v = get_edges(g);
    sort_edge_vector(v);

    for (int i = 0; i < v.count; i++) {
        EDGE e = v.edges[i];
        graph_remove_link(g, e.vertex1, e.vertex2);

        if (!has_way(g, e.vertex1) || !has_way(g, e.vertex2)) {
            graph_set_link(g, e.vertex1, e.vertex2, e.weight);
        }
    }

    free(v.edges);
}

int main() {
    FILE* fin = fopen("graph2.txt", "r");
    if (!fin) return -1;
    GRAPH* g = read_graph(fin);
    fclose(fin);

    build_spanning_tree(g);

    FILE* out = fopen("graph3.txt", "w");
    print_graph(g, out);
    fclose(out);
    graph_delete(g);
    return 0;
}
