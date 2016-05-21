# include <stdlib.h>
# include <stdio.h>

/* Структура - узел дерева */
typedef struct _node {
	int data;
	struct _node *left;
	struct _node *right;
} Node;
/* Вспомогательная функция создания узла */
Node* create_tree_node(int data) {
	Node* node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}
/* Вставка значения в дерево */
void insert_in_tree(Node** root, int data) {
	/* Если поддерево пусто - то создаём его корень */
	if ((*root) == NULL) {
		(*root) = create_tree_node(data);
		return;
	}
	/* Если элемент уже лежит в дереве - то ничего добавлять уже не нужно */
	if ((*root)->data == data) return;
	/* Сравниваем добавляемое значение со значение корня */
	if (data < (*root)->data) {
		/* Если оно меньше, то пытаемся вставить элемент в левое поддерево */
		insert_in_tree(&((*root)->left), data);
	} else {
		/* Если боольше, то в правое */
		insert_in_tree(&((*root)->right), data);
	}
}
/* Инфиксная распечатка дерева */
void print_tree(Node* root) {
	if (root == NULL) return;
	print_tree(root->left);
	printf("%i ", root->data);
	print_tree(root->right);
}
/* Удаление дерева */
void delete_tree(Node* root) {
	if (root == NULL) return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

/* Вызовы функций */
	Node *root; /* Сначала нужно объявить переменную - указатель на корень дерева */
	
	/* Вставить в дерево некоторое значение x */
	insert_in_tree(&root, x);
	
	/* Распечатать дерево */
	print_tree(root);
	
	/* Удалить дерево */
	delete_tree(root);
