# include "graphs.h"
# include <stdlib.h>

// Fill in the matrix provides values
void _fill_matrix(int *m, int n, int v) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            *(m + (i * n + j)) = v;
        }
    }
}

// Create new graph with a certain number of vertices
GRAPH* graph_create(int count_of_vertices, int mode) {
    GRAPH* graph = (GRAPH*) malloc(sizeof(GRAPH));
    graph->adjacency_matrix = (int*) malloc(sizeof(int) * count_of_vertices * count_of_vertices);
    graph->count_of_vertices = count_of_vertices;
    graph->mode = mode;
    _fill_matrix(
        graph->adjacency_matrix,
        graph->count_of_vertices,
        GRAPH_INF_WEIGHT
    );
    return graph;
}

GRAPH* graph_create_from_adjacency_matrix(int n, int mode, int* m) {
    GRAPH* g = graph_create(n, mode);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            graph_set_link(g, i, j, *(m + j * n + i));
        }
    }
    return g;
}

GRAPH* graph_copy(GRAPH* g) {
    return graph_create_from_adjacency_matrix(
        g->count_of_vertices,
        g->mode,
        g->adjacency_matrix
    );
}

void graph_set_link(GRAPH* graph, int vertex1, int vertex2, int weight) {
    int index = vertex2 * graph->count_of_vertices + vertex1;
    *(graph->adjacency_matrix + index) = weight;
    if (graph->mode == GRAPH_UNDERICTED) {
        index = vertex1 * graph->count_of_vertices + vertex2;
        *(graph->adjacency_matrix + index) = weight;
    }
}

int graph_get_link(GRAPH* graph, int vertex1, int vertex2) {
    int index = vertex2 * graph->count_of_vertices + vertex1;
    return *(graph->adjacency_matrix + index);
}

void graph_add_link(GRAPH* graph, int vertex1, int vertex2) {
    graph_set_link(graph, vertex1, vertex2, 1);
}

void graph_remove_link(GRAPH* graph, int vertex1, int vertex2) {
    graph_set_link(graph, vertex1, vertex2, GRAPH_INF_WEIGHT);
}

int graph_has_link(GRAPH* graph, int vertex1, int vertex2) {
    return graph_get_link(graph, vertex1, vertex2) != GRAPH_INF_WEIGHT;
}

void graph_delete(GRAPH* g) {
    free(g->adjacency_matrix);
    free(g);
}

inline int graph_count_of_vertices(GRAPH* g) {
    return g->count_of_vertices;
}
