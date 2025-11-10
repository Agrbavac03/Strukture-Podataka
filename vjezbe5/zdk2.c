#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char* STRING;

typedef struct postfix* Pos;
typedef struct postfix {
	double number;
	Pos next;
}postfix;


int push(Pos, double);
double pop(Pos);
int readFile(STRING, int[], int*);
int all(Pos, int[], int);
void ispis(Pos);


int main() {
	postfix Head = { 0, NULL };
	STRING podaci = "podaci.txt";

	int noe = 0;	//number of elements
	int A[100];

	readFile(podaci, A, &noe);
	printf("number of elements: %d\n", noe);
	printf("\n");

	all(&Head, A, noe);
	printf("\n");
	return 0;
}


int push(Pos P, double num) {
	Pos temp;
	Pos q = malloc(sizeof(postfix));
	if (q == NULL) {
		printf("Error with malloc.");
	}
	temp = P;

	if (temp->next == NULL) {			//unos ako je prazna lista
		q->number = num;
		q->next = temp->next;
		P->next = q;
		return 0;
	}
	else {
		Pos second = temp->next;		//unos ako ima nekih elemenata
		q->number = num;
		q->next = second;
		P->next = q;
		return 0;
	}
}

double pop(Pos Head) {
	if (Head->next == NULL) {
		return 0;
	}
	double poped = 0;
	Pos first = Head->next;

	if (Head->next->next == NULL) {
		Head->next = NULL;
		poped = first->number;
		free(first);
		return poped;
	}

	Pos second = first->next;

	Head->next = first->next;
	poped = first->number;
	
	free(first);

	return poped;
}

int readFile(STRING filename, int lista[100], int* numOfElements) {
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error when loading file.\n");
		return 0;
	}

	char ch;
	int br = 0;
	while ((ch = fgetc(fp)) != EOF && ch != '\n') {
		if (isdigit(ch)) {
			int num = ch - '0';						// convert char digit to int
			//printf("Integer: %d\n", num);
			lista[br] = num;
			br++;
		}
		else {
			//printf("Character: %c\n", ch);
			lista[br] = ch;
			br++;
		}
	}
	fclose(fp);
	*numOfElements = br;
	printf("Reading file succesful.\n");
	return 0;
}

int all(Pos P, int lista[], int numOfEl) {
	int i = 0;

	while (i != numOfEl) {
		while (i < numOfEl && lista[i] != 42 && lista[i] != 43 && lista[i] != 45 && lista[i] != 47) {
			push(P, lista[i]);
			printf("Added to top of stack: %d\n", lista[i]);					//Push number if not character
			i++;
			
		}
		if (i >= numOfEl) break;			//break ako je doslo do kraja liste

		double a, b, res;
		switch (lista[i]) {						//switch case za sve operatore preko ASCI
		case 42:
			printf("Multiply.\n");
			a = pop(P);
			b = pop(P);
			res = b * a;
			push(P, res);
			printf("---------------------------\n");
			ispis(P);
			printf("---------------------------\n");
			break;
		case 43:
			printf("Addition.\n");
			a = pop(P);
			b = pop(P);
			res = b + a;
			push(P, res);
			break;
		case 45:
			printf("Substraction.\n");
			a = pop(P);
			b = pop(P);
			res = b - a;
			push(P, res);
			break;
		case 47:
			printf("Division.\n");
			a = pop(P);
			b = pop(P);
			res = b / a;
			push(P, res);
			break;
		}
		i++;
	}
	printf("Final result: %.2f", P->next->number);
	return 0;
}

void ispis(Pos P) {								//Ispis vezane liste
	Pos temp = P->next;

	while (temp != NULL) {
		printf("%.2f,\t", temp->number);
		temp = temp->next;
	}
	printf("\n");
	return 0;
}