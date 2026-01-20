#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TS 11  //Table size

typedef struct city* treePos;
typedef struct city {
	char cityName[50];
	int population;
	treePos left;
	treePos right;
}city;

typedef struct country* Pos;		
typedef struct country {
	char nameOfCountry[50];
	int key;
	Pos next;
	treePos root;
}country;

Pos hashTable[TS];

int hashFunction(char*);
int insertCountry(char*, char*);
void insertCountrySorted(Pos*, Pos);

treePos insertCity(treePos, char*, int);

void printCityTree(treePos);
void printHashTable(void);

Pos findCountry(char*);
void findCities(treePos, int);
void search();


int main() {
	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) {
		printf("Cannot open drzave.txt\n");
		return 1;
	}

	for (int i = 0; i < TS; i++)
		hashTable[i] = NULL;

	char country[50], file[50];

	while (fscanf(fp, "%s %s", country, file) == 2) {
		insertCountry(country, file);
	}
	fclose(fp);

	printHashTable();

	search();

	return 0;
}

int hashFunction(char* countryName) {
	int sum = 0;
	for (int i = 0; i < 5 && countryName[i] != '\0'; i++) {
		sum += (int)countryName[i];
	}
	return sum % TS;
}

int insertCountry(char* countryName, char* filename) {
	int index = hashFunction(countryName);

	Pos newCountry = malloc(sizeof(country));
	if (!newCountry) {
		printf("Memory allocation error\n");
		return 0;
	}

	strcpy(newCountry->nameOfCountry, countryName);
	newCountry->root = NULL;
	newCountry->next = NULL;

	// ucitavanje gradova
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Cannot open %s\n", filename);
		return 0;
	}

	char city[50];
	int population;

	while (fscanf(fp, "%[^,],%d\n", city, &population) == 2) {
		newCountry->root = insertCity(newCountry->root, city, population);
	}
	fclose(fp);

	insertCountrySorted(&hashTable[index], newCountry);
	return 1;
}

void insertCountrySorted(Pos* head, Pos newCountry) {
	if (*head == NULL || strcmp((*head)->nameOfCountry, newCountry->nameOfCountry) > 0) {
		newCountry->next = *head;
		*head = newCountry;
		return;
	}

	Pos curr = *head;
	while (curr->next && strcmp(curr->next->nameOfCountry, newCountry->nameOfCountry) < 0)
		curr = curr->next;

	newCountry->next = curr->next;
	curr->next = newCountry;
}

treePos insertCity(treePos root, char* cityName, int population) {
	if (root == NULL) {
		treePos newCity = malloc(sizeof(city));
		if (!newCity) {
			printf("Memory allocation error\n");
			return NULL;
		}

		strcpy(newCity->cityName, cityName);
		newCity->population = population;
		newCity->left = NULL;
		newCity->right = NULL;

		return newCity;
	}

	if (population < root->population) {
		root->left = insertCity(root->left, cityName, population);
	}
	else {
		root->right = insertCity(root->right, cityName, population);
	}

	return root;
}

void printCityTree(treePos root) {
	if (root == NULL)
		return;

	printCityTree(root->left);
	printf("\t%s - %d\n", root->cityName, root->population);
	printCityTree(root->right);
}

void printHashTable(void) {
	for (int i = 0; i < TS; i++) {
		printf("Hash[%d]:\n", i);

		Pos curr = hashTable[i];
		while (curr != NULL) {
			printf("Drzava: %s\n", curr->nameOfCountry);
			printCityTree(curr->root);
			curr = curr->next;
		}
		printf("\n");
	}
}

//find funkcije

Pos findCountry(char* countryName) {
	int index = hashFunction(countryName);
	Pos curr = hashTable[index];

	while (curr != NULL) {
		if (strcmp(curr->nameOfCountry, countryName) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

void findCities(treePos root, int minPopulation) {
	if (root == NULL) {
		return;
	}

	findCities(root->left, minPopulation);

	if (root->population > minPopulation) {
		printf("\t%s - %d stanovnika\n", root->cityName, root->population);
	}

	findCities(root->right, minPopulation);
}

void search() {
	char countryName[50];
	int minPop;

	printf("Enter country for search: ");
	scanf("%49s", countryName);
	printf("Enter min. population: ");
	scanf("%d", &minPop);

	Pos selected = findCountry(countryName);

	if (selected == NULL) {
		printf("Drzava nije pronadena.\n");
	}
	else {
		printf("Gradovi sa vise od %d stanovnika su: \n", minPop);
		findCities(selected->root, minPop);
	}

}
