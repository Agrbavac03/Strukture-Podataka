#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* STRING;

typedef struct city* treePos;
typedef struct city {
	char cityName[50];
	int population;
	treePos left;
	treePos right;
}city;

typedef struct country* Pos;
typedef struct country {
	char countryName[50];
	Pos next;
	treePos root;
}country;


//funkcije
STRING openFile(FILE*, STRING, int);
int splitString(Pos, STRING);
int splitStringByComa(Pos, STRING);
int addToList(Pos, STRING, STRING);
int leftRightChoice(treePos*, STRING, int);

int printTree(treePos);
void printAll(Pos);

int search(Pos);
Pos findCountry(Pos, STRING);
int findCities(treePos, int);


int main() {
	country Head = {"",NULL,NULL};


	FILE* fp = fopen("drzave.txt", "r");
	if (fp == NULL) {
		printf("Error when opening file drzave.txt\n");
		return NULL;
	}

	char line[256];

	while (openFile(fp, line, 256)) {
		splitString(&Head, line);			
	}
	fclose(fp);

	printAll(&Head);

	search(&Head);

	return 0;
}

STRING openFile(FILE* filename, STRING buffer, int size) {
	if (fgets(buffer, size, filename) != NULL) {
		return buffer;
	}
	return NULL;
}

int splitString(Pos head, STRING buffer) {
	STRING name = strtok(buffer, " ");	
	//printf("%s\t\t\n", name);					//split za drzavu

	STRING nameOfFile = strtok(NULL, " ");		//split za file name
	nameOfFile[strcspn(nameOfFile, "\n")] = 0;   //uklanja '\n'
	//printf("%s\t\t\n", nameOfFile);

	addToList(head, name, nameOfFile);			//dodavanje drzava u vezanu listu
	return 1;
}

int addToList(Pos head, STRING country, STRING filename) {
	Pos q = malloc(sizeof(struct country));
	if (q == NULL) {
		printf("Error while malloc");
		return 0;
	}
	strcpy(q->countryName, country);
	q->root = NULL;

	Pos prev = head;
	Pos curr = head->next;

	while (curr != NULL && strcmp(curr->countryName, country) < 0) {
		prev = curr;
		curr = curr->next;
	}

	q->next = curr;
	prev->next = q;							//drzava dodana u vezanu listu
														
														
				//dodavanje gradova u stablo
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error when opening file pojedina drzava\n ");
		return 0;
	}
	char line[256];
	while (openFile(fp, line, 256)) {
		splitStringByComa(q, line);		//dijeljenje linije pa spremanje u stablo
	}

	fclose(fp);
	return 1;
}

int splitStringByComa(Pos head, STRING buffer) {		//dijeljenje stringa po ","
	STRING city = strtok(buffer, ",");
	//printf("%s\t\t\n", city);

	STRING popStr = strtok(NULL, ",");
	int population = atoi(popStr);
	//printf("%d\t\t\n", population);					

	leftRightChoice(&head->root, city, population);
	return 1;
}


int leftRightChoice(treePos* root, STRING ct, int popul) {			//funkcija za trazenje tocnog mjesta za stavit grad
	if (*root == NULL) {							//ako je prazan
		treePos new = malloc(sizeof(city));		//odma se dodaje na to mjesto
		if (new == NULL) {
			printf("Error while malloc");
			return 0;
		}
		strcpy(new->cityName, ct);
		new->population = popul;
		new->left = NULL;
		new->right = NULL;

		*root = new;		//spremanje new(prvi element stabla) kao root element drzave iz vezane liste
		return 1;
	}
	else {
		if ((*root)->population < popul) {
			return leftRightChoice(&(*root)->right, ct, popul);
		}
		else{
			return leftRightChoice(&(*root)->left, ct, popul);
		}
	}
}

//ispis

int printTree(treePos root){
	if (root == NULL) {
		return 0;
	}

	printTree(root->left);
	printf("\t%s - %d\n", root->cityName, root->population);
	printTree(root->right);
	return 1;
}

void printAll(Pos head){
	Pos temp = head->next;

	while (temp != NULL) {
		printf("Drzava: %s\n", temp->countryName);
		printTree(temp->root);
		printf("\n");

		temp = temp->next;
	}
}

//pretrazivaanje

int search(Pos head) {
	char country[50];
	int minPop;
	
	printf("Enter country for search: ");
	scanf("%49s", country);
	printf("Enter min. population: ");
	scanf("%d", &minPop);

	Pos selected = findCountry(head, country);
	if (selected == NULL) {
		return 0;
	}

	printf("Cities with bigger population than %d are\n", minPop);

	findCities(selected->root, minPop);
	return 1;
}

Pos findCountry(Pos head, STRING country) {
	Pos temp = head->next;

	while (temp != NULL) {
		if (strcmp(temp->countryName, country) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	printf("Country does not exist.");
	return NULL;
}

int findCities(treePos root, int bottomLine) {
	if (root == NULL) {
		return 1;
	}
	findCities(root->left, bottomLine);

	if (root->population > bottomLine) {
		printf("\t%s\t- %d\n",root->cityName, root->population);
	}

	findCities(root->right, bottomLine);
	return 1;
}
