#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* STRING;

typedef struct dir* PosDir;
typedef struct dir {
	char name[64];
	PosDir next;		//sljedeci u listi
	PosDir subDir;		//subDirectory, onaj ispod
}dir;

typedef struct stack* PosStack;
typedef struct stack {
	PosDir dirLevel;
	PosStack next;
}stack;

int printAll(PosDir);
int printCurrentPos(PosStack);
int addSubDir(PosDir, STRING);		//dodavanje u taj folder koji smo zadali kao PosDir
int cd(PosDir, PosStack);
PosDir findSubDir(PosDir P, STRING name);

int cdIn(PosStack*, STRING);
int cdUp(PosStack*);
int kretanje(PosDir, PosStack);

int main() {
	dir headDir = {"C",NULL,NULL};
	PosStack headStack = (PosStack)malloc(sizeof(stack));
	if (headStack == NULL) {
		printf("Error while trying to malloc! ");
		return 1;
	}
	headStack->dirLevel = &headDir;
	headStack->next = NULL;

	kretanje(&headDir, headStack);
	
	return 0;
}

int printAll(PosDir P) {
	PosDir temp = P;

	if (temp == NULL) {
		printf("\tEmpty\n");
		return 1;
	}

	while (temp != NULL) {
		printf("\t%s\n", temp->name);
		temp = temp->next;
	}
	return 1;
}

int printCurrentPos(PosStack PS) {
	PosStack temp = PS;					
	if (temp == NULL) return 1;
	printCurrentPos(temp->next);
	printf("%s|", temp->dirLevel->name);
	return 1;
}


int addSubDir(PosDir P, STRING filename) {
	if (P == NULL) return 0;
	PosDir temp = P;

	PosDir q;									
	q = malloc(sizeof(dir));
	if (q == NULL) {
		printf("Error while trying to malloc\n");
		return 0;
	}
	strcpy(q->name, filename);
	q->subDir = NULL;
	q->next = temp->subDir;
	temp->subDir = q;
}


PosDir findSubDir(PosDir P, STRING name) {
	if (P == NULL) return NULL;

	PosDir temp = P->subDir;
	while (temp != NULL) {
		if (strcmp(temp->name, name) == 0) return temp;
		temp = temp->next;
	}
	return NULL;
}


int cdIn(PosStack* stackTop, STRING name) {
	if (stackTop == NULL || *stackTop == NULL) return 0;

	PosDir curr = (*stackTop)->dirLevel;
	PosDir destination = findSubDir(curr, name);

	if (!destination) {
		printf("Directory `%s` does not exist in `%s`.\n", name, curr->name);
		return 0;
	}

	PosStack new = (PosStack)malloc(sizeof(stack));
	if (!new) {
		printf("Error while trying to malloc\n");
		return 0;
	}

	new->dirLevel = destination;
	new->next = *stackTop;
	*stackTop = new;

	return 1;
}


int cdUp(PosStack* stackTop) {
	if (stackTop == NULL || *stackTop == NULL) return 0;

	if ((*stackTop)->next == NULL) {
		printf("You are in root directory. Going up is not possible.\n");
		return 0;
	}
	
	PosStack temp = *stackTop;
	*stackTop = temp->next;
	free(temp);

	return 1;
}


int kretanje(PosDir PD, PosStack stackTop) {
	int izbor = 0;
	char ime[64];
	printf("1 - md\n");
	printf("2 - cd dir\n");
	printf("3 - cd..\n");
	printf("4 - dir)\n");
	printf("5 - exit\n");

	do {
		printCurrentPos(stackTop);
		printf(": ");
		if (scanf("%d", &izbor) != 1) {
			printf("Wrong input!\n");
		}
		switch (izbor) {
		case 1:
			scanf("%63s", ime);
			if (addSubDir(stackTop->dirLevel, ime)) {		//na poziciji zadnjeg na stacku dodajemo ime
				printf("Directory '%s' created.\n", ime);
			}
			else {
			printf("Error while creating dir.\n");
			}
			break;

		case 2:
			scanf("%63s", ime);
			cdIn(&stackTop, ime);
			break;

		case 3:
			cdUp(&stackTop);
			break;

		case 4:
			printf("%s:\n", stackTop->dirLevel->name);
			printAll(stackTop->dirLevel->subDir);
			break;

		case 5:
			printf("exiting...\n");
			break;

		default:
			printf("Unknown operation.\n");
		}

		printf("\n");



	} while (izbor != 5);

	return 1;
}
