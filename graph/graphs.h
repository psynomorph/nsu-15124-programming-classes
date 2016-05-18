# ifndef GRAPHS_H_INCLUDED
# define GRAPHS_H_INCLUDED

# include <limits.h>
/* Значение соответвствующие бесконечному весу в графе
   Обозначает отсутсвие связи между вершинами */ 
# define GRAPH_INF_WEIGHT INT_MAX / 2 

/* Режимы направленности графа */
enum GRAPH_MODES {
    GRAPH_UNDERICTED, /* Не направленный */
    GRAPH_DERICTED /* Направленный */
};

/* Структура графа */
typedef struct _graph {
    int count_of_vertices;  /* Количество вершин */
    int mode; /* Режим направленности */
    int *adjacency_matrix; /* Матрица смежности */
} GRAPH;
/* Создать новый граф с заданным количеством вершин
   Все связи будут установлены в GRAPH_INF_WEIGHT
   Первый параметр - количество вершин, второй направленность графа */
GRAPH* graph_create(int, int);
/* Создать новый граф с заданной матрицей смежности */
/* (Количество вершин, Направленность, Матрица смежности */
GRAPH* graph_create_from_adjacency_matrix(int, int, int*);
/* Создать копию графа */
GRAPH* graph_copy(GRAPH*);
/* Удалить граф */
void graph_delete(GRAPH*);
/* Возвращает количество вершин в графе */
int graph_count_of_vertices(GRAPH*);
/* Устанавливает связь между вершинами param2 и param3 с весом param4 */
void graph_set_link(GRAPH*, int, int, int);
/* Устанавливает связь между вершинами param2 и param3 с весом 1 */
void graph_add_link(GRAPH*, int, int);
/* Удаляет (ставит вес GRAPH_INF_WEIGHT) связь между вершинами param2 и param3 */
void graph_remove_link(GRAPH*, int, int);
/* Возвращает вес связи между вершинами param2 и param3 */
int graph_get_link(GRAPH*, int, int);
/* Проверяет, есть ли связь между вершинами param2 и param3 
int graph_has_link(GRAPH*, int, int);

# endif /* GRAPHS_H_INCLUDED */
