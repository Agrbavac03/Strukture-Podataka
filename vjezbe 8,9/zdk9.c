#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


typedef struct tree* Pos;

typedef struct tree {
    int value;
    Pos left;
    Pos right;
} tree;


Pos insert(int, Pos);
Pos deleteAll(Pos);
Pos deleteNode(int, Pos);
Pos findMin(Pos);
void inorder(Pos);

int replace(Pos);
void inorderFile(Pos, FILE*);

int main() {
    Pos root = NULL;

    root = insert(2, root);
    root = insert(5, root);
    root = insert(7, root);
    root = insert(8, root);
    root = insert(11, root);
    root = insert(1, root);
    root = insert(4, root);
    root = insert(2, root);
    root = insert(3, root);
    root = insert(7, root);

    FILE* fp = fopen("podaci.txt", "w");
    if (fp == NULL) {
        printf("Error while opening podaci.txt \n");
        return 1;
    }

    printf("Inorder 1: ");
    inorder(root);

    replace(root);

    printf("\nInorder 2: ");
    inorder(root);

    inorderFile(root, fp);

    root = deleteAll(root);
    return 0;
}


Pos insert(int x, Pos P) {
    if (P == NULL) {
        Pos q = malloc(sizeof(tree));
        if (q == NULL) {
            printf("Malloc error\n");
            return NULL;
        }
        q->value = x;
        q->left = q->right = NULL;
        return q;
    }

    if (x > P->value)
        P->left = insert(x, P->left);
    else
        P->right = insert(x, P->right);

    return P;
}

Pos deleteAll(Pos P) {
    if (P != NULL) {
        deleteAll(P->left);
        deleteAll(P->right);
        free(P);
    }
    return NULL;
}

void inorder(Pos P) {
    if (P != NULL) {
        inorder(P->left);
        printf("%d ", P->value);
        inorder(P->right);
    }
}

Pos findMin(Pos P) {
    if (P == NULL) {
        return NULL;
    }

    while (P->right != NULL) {
        P = P->right;
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

int replace(Pos P) {
    if (P == NULL) return 0;

    int Lsum = replace(P->left);
    int Rsum = replace(P->right);

    int old = P->value;
    P->value = Lsum + Rsum;

    return P->value + old;
}

void inorderFile(Pos P, FILE* file) {
    if (P != NULL) {
        inorderFile(P->left, file);
        fprintf(file, "%d", P->value);
        inorderFile(P->right, file);
    }
}