/* Узел списка */
typedef struct _list_node {
	struct _list_node* next; /* Следующий узел */
	int value; /* Значение */
} Node;

/* Структура описывающая список */
typedef struct _list {
	Node *head, *tail; /* Указатели на хвост и голову списка */
	int size; /* Размер списка */
} List;

/* Создать список */
List* create_list() {
	List* l = (List*) malloc(sizeof(List));
	l->size = 0;
	l->tail = l->head = NULL;
	return l;
}

/* Создать узел */
Node* create_node() {
	Node* n = (Node*) malloc(sizeof(Node));
	n->next = NULL;
	return n;
}

/* Вставить узел в начало списка */
void shift_node(List* l, Node* n) {
	if (!l->size) {
		l->head = l->tail = n;
		n->next = NULL;
	} else {
		n->next = l->head;
		l->head = n;
	}
	l->size++;
}

/* Добавить значение в начало списка */
void shift(List* l, int v) {
	/* Созаём узел */
	Node* n = create_node();
	n->value = v;
	/* И вставляем его в начало */
	shift_node(l, n);
}

/* Вставить узел new_node после node */
void insert_node_after(List* l, Node* n, Node* new_node) {
	if (n == NULL) {
		return shift_node(l, new_node);
	}
	if (n == l->tail) {
		l->tail = new_node;
	}
	n->next = new_node;
	l->size++;
}

/* Вставить значение value после узла n */
void insert_after(List* l, Node* n, int value) {
	Node *node = create_node();
	n->value = value;
	insert_node_after(l, n, node);
}

/* Вставить значение v в конец списка */
void append(List* l, int v) {
	/* Это значит вставить элемент сразу за хвостом */
	insert_after(l, l->tail, v);	
}

/* Удалить список */
void delete_list(List* l) {
	Node *n, *nn;
	n = l->head;
	while(n != NULL) {
		nn = n;
		n = n->next;
		free(nn);
	}
	free(l); 
}
/* Так как список односвязный, то мы не можем быстро удалить выбранный узел,
   так как нам пришлось бы искать предшествующий ему, а это сложность O(n),
   главное же, что требуется от списков - вставка и удаление за O(const)
   Зато можно удалить следующий за ним. 
   Функция удаляет следующий узел после n
*/ 
void delete_next_node(List* l, Node* n) {
	Node* next = n->next;
	n->next - next->next;
	if (next == l->tail) {
		l->tail = n;
	}
	free(next);
	l->size--;
}

/* Удалить первый элемент */
void delete_first(List* l) {
	if (l->head == NULL) return;
	Node* n = l->head;
	l->head = n->next;
	if (l->tail == n) l->tail = NULL;
	free(n);
	l->size--;
}

/* Распечатать список */
void print_list(List* l) {
	Node* n;
	for (n = l->head; n != l->tail->next; n = n->next) {
		printf("%d ", n->value);
	}
	printf("\n");
}
