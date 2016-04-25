# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define STR_LENGTH 128

typedef struct _str_node {
	char str[STR_LENGTH];
	struct _str_node *left, *right;
} STR_NODE;

STR_NODE* create_node(char* str) {
	STR_NODE* node = (STR_NODE*) malloc(sizeof(STR_NODE));
	node->left = node->right = NULL;
	strcpy(node->str, str);
	return node;
}

void insert_node(STR_NODE **root, STR_NODE *node) {
	if (!(*root)) {
		*root = node;
		return;
	}
	if (strcmp((*root)->str, node->str) >= 0) {
		insert_node(&((*root)->left), node);
	} else {
		insert_node(&((*root)->right), node);
	}
}

void map_tree(STR_NODE* node, FILE* fout) {
	if (!node) return;
	if (node->left) map_tree(node->left, fout);
	fprintf(fout, "%s ", node->str);
	if (node->right) map_tree(node->right, fout);
}

void delete_tree(STR_NODE* root) {
	if (!root) return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

int main() {
	FILE* fin = fopen("input.txt", "r");
	if (!fin) return -1;
	STR_NODE *root = NULL;
	while (!feof(fin)) {
		char str[STR_LENGTH];
		fscanf(fin, "%s", str);
		insert_node(&root, create_node(str));
	}
	fclose(fin);
	
	FILE* fout = fopen("output.txt", "w");
	map_tree(root, fout);
	fclose(fout);
	delete_tree(root);
	return 0;
}
