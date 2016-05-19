# include <stdlib.h>
# include <stdio.h>

/* Узел списка */
typedef struct _node
{
    struct _node *next;
    int value;
} Node;

/* Структура - циклический список */
typedef struct _cycle_list
{
    Node *head;
    Node *tail;
} CycleList;

/* Создать циклический список */
CycleList* cl_create() {
    CycleList *cl = (CycleList*) malloc(sizeof(CycleList));
    cl->head = cl->tail = NULL;
    return cl;
}

/* Создать узел списка */
Node* cl_create_node(int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->next = NULL;
    node->value = value;
    return node;
}

/* Вставить значение value в конец списка */
void cl_append(CycleList* cl, int value) {
    Node *node = cl_create_node(value);
    if (cl->tail == NULL) {
        cl->head = cl->tail = node;
        node->next = node;
    } else {
        node->next = cl->head;
        cl->tail->next = node;
        cl->tail = node;
    } 
}

/* Распечатать список */
void cl_print(CycleList* cl) {
    Node* n = cl->head;
    do {
        printf("%i ", n->value);
        n = n->next;
    } while (n != cl->head);
    printf("\n");
}

/* Удалить узел, следующий за node */
void cl_remove_next_node(CycleList* cl, Node* node) {
    Node* next_node = node->next;
    if (next_node == node) {
        free(node);
        cl->tail =  cl->head = NULL;
        return;
    }
    if (next_node == cl->head) {
        cl->head = cl->head->next;
    }
    if (next_node == cl->tail) {
        cl->tail = node;
    }
    node->next = next_node->next;
    free(next_node);
}

/* Удалить список */
void cl_delete(CycleList* cl) {
    Node *node = cl->head;
    if (node != NULL) {
        while (node != cl->tail) {
            Node* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(cl);
}

int main() {
    int i, n;
    /* Считываем количество узлов */
    scanf("%i", &n);
    /* Создаём циклический список */
    CycleList *cl = cl_create();

    for (i = 0; i < n; i++) {
        int t;
        scanf("%i", &t); /* Считываем значения узлов */
        cl_append(cl, t); /* И заносим в список */
    }
    cl_print(cl);
    scanf("%i", &n); /* Номер узла, который будет удалятся */
    n--; /* Чтобы дойти до n узла нужен n - 1 переход */

    /* Как я писал, в односвязном списке нельзя так просто взять 
           и удалить выбранный узел. Зато легко удалить следующий за ним.
           Воспользуемся свойством циклического списка (cl->tail->next = cl->head)
           и начнём обход с cl->tail. Тогда при удалении следующего, мы будеи удалять необходимый */
    Node *node = cl->tail;
    while (cl->head != cl->tail) {
        for (i = 0; i < n; i++) node = node->next; // Перемещаемся на необходимый узел
        cl_remove_next_node(cl, node);
        cl_print(cl);
    }

    printf("%i\n", cl->head->value);
    cl_delete(cl);
    return 0;
}
