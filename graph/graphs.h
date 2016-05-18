# ifndef GRAPHS_H_INCLUDED
# define GRAPHS_H_INCLUDED

# include <limits.h>

# define GRAPH_INF_WEIGHT INT_MAX / 2

enum GRAPH_MODES {
    GRAPH_UNDERICTED,
    GRAPH_DERICTED
};

typedef struct _graph {
    int count_of_vertices;
    int mode;
    int *adjacency_matrix;
} GRAPH;

GRAPH* graph_create(int, int);
GRAPH* graph_create_from_adjacency_matrix(int, int, int*);
GRAPH* graph_copy(GRAPH*);
void graph_delete(GRAPH*);
int graph_count_of_vertices(GRAPH*);
/* Work with links */
void graph_set_link(GRAPH*, int, int, int);
void graph_add_link(GRAPH*, int, int);
void graph_remove_link(GRAPH*, int, int);
int graph_get_link(GRAPH*, int, int);
int graph_has_link(GRAPH*, int, int);

# endif /* GRAPHS_H_INCLUDED */
