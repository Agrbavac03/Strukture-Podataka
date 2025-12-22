#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tree* Pos;
typedef struct tree {
	int value;
	Pos left;
	Pos right;
}tree;

Pos deleteAll(Pos);
Pos insert(int, Pos);
Pos deleteNode(int, Pos);
Pos findMin(Pos);
Pos find(int, Pos);

void inorder(Pos);
void preorder(Pos);
void postorder(Pos);

int main() {
	Pos root = NULL;

	root = insert(4, root);
	root = insert(2, root);
	root = insert(6, root);
	root = insert(1, root);
	root = insert(3, root);
	root = insert(5, root);
	root = insert(7, root);

	printf("Inorder: ");
	inorder(root);

	printf("\nPreorder: ");
	preorder(root);

	printf("\nPostorder: ");
	postorder(root);

	printf("\n\Deleting - 4\n");
	root = deleteNode(4, root);


	printf("Inorder after delete: ");
	inorder(root);

	root = deleteAll(root);
	return 0;
}


Pos deleteAll(Pos P) {
	if (P != NULL) {
		deleteAll(P->left);
		deleteAll(P->right);
		free(P);
	}
	return NULL;
}

Pos insert(int x, Pos P) {
	if (P == NULL) {
		Pos q;
		q = malloc(sizeof(tree));
		if (q == NULL) {
			printf("Error when trying to malloc.\n");
			return NULL;
		}
		q->value = x;
		q->right = NULL;
		q->left = NULL;
		return q;
	}
	else if (P->value > x) {
		P->left = insert(x, P->left);
	}
	else if (P->value < x) {
		P->right = insert(x, P->right);
	}
	return P;
}

Pos deleteNode(int x, Pos P) {
	if (P == NULL) return NULL;
	if (P->value > x) {
		P->left = deleteNode(x, P->left);
	}
	else if (P->value < x) {
		P->right = deleteNode(x, P->right);
	}
	else {
		//znaci da je P->value == x
		if (P->left != NULL && P->right != NULL) {
			Pos temp = findMin(P->right);
			P->value = temp->value;
			P->right = deleteNode(P->value, P->right);
		}
		else {
			Pos temp = P;
			if (P->left == NULL) {
				P = P->right;
			}
			else {
				P = P->left;
			}
			free(temp);
		}
	}
	return P;
}

Pos findMin(Pos P) {
	if (P == NULL) {
		return NULL;
	}

	while (P->left != NULL) {
		P = P->left;
	}

	return P;
}

Pos find(int x, Pos P) {
	if (P == NULL)
		return NULL;

	if (x < P->value) return find(x, P->left);
	else if (x > P->value) return find(x, P->right);
	else return P;
}


void inorder(Pos P) {
	if (P != NULL) {
		inorder(P->left);
		printf("%d ", P->value);
		inorder(P->right);
	}
}


void preorder(Pos P) {
	if (P != NULL) {
		printf("%d ", P->value);
		preorder(P->left);
		preorder(P->right);
	}
}


void postorder(Pos P) {
	if (P != NULL) {
		postorder(P->left);
		postorder(P->right);
		printf("%d ", P->value);
	}
}