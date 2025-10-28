#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* STRING;
typedef struct Person* Pos;

typedef struct Person {
	char* name;
	char* surname;
	int year;
	Pos next;
}person;


int unosPocetak(STRING, STRING, int, Pos);
void ispis(Pos);
int unosKraj(STRING, STRING, int, Pos);
Pos Trazi(STRING, Pos);
void Brisi(STRING, Pos);
int dodajIza(STRING, STRING, STRING, int, Pos);
int dodajIspred(STRING, STRING, STRING, int, Pos);
void upisiudat(Pos);
void sortiraj(Pos);
int izbrojiRetke(STRING);
int citajIzdat(STRING, Pos);



int main() {															//	<- main
	person Head = { NULL, NULL, 0, NULL };
	unosPocetak("Ivan", "Zelic", 2005, &Head);
	unosPocetak("Sime", "Zebic", 2005, &Head);
	unosKraj("Ante", "Poljak", 2005, &Head);
	unosKraj("Mate", "Simic", 2004, &Head);
	unosPocetak("Luka", "Bertic", 2003, &Head);
	ispis(&Head);
	printf("-------------------------------------------\n");
	/*
	if (Trazi("Zelic", &Head) == NULL) {
		printf("Person is not in list.");
	}
	else {
		printf("Person is in list.\n");
	}

	Brisi("Zelic", &Head);
	printf("--------------------------------------\n");
	
	
	dodajIza("Poljak", "Luka", "Lemo", 2003, &Head);
	dodajIspred("Poljak", "Marin", "Lukic", 2001, &Head);

	ispis(&Head);
	upisiudat(Head.next);
	citajIzdat("podaci.txt", &Head);
	printf("Zadnji ispis: ---------------------------------------------\n");
	ispis(Head.next);
	*/
	sortiraj(&Head);
	ispis(Head.next);
	return 0;
}

int unosPocetak(STRING name, STRING surname, int year, Pos P) {			// <- unos na pocetak
	Pos q;
	q = (Pos)malloc(sizeof(person));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return 0;
	}

	q->name = name;
	q->surname = surname;
	q->year = year;
	q->next = P->next;
	P->next = q;

	return 0;
}

void ispis(Pos P) {														//	<- Ispis
	while (P != NULL) {
		printf("%s\t%s\t%d\n", P->name, P->surname, P->year);
		P = P->next;
	}
}

int unosKraj(STRING name, STRING surname, int year, Pos P) {			//	<- Unos na kraj
	Pos q;
	q = (Pos)malloc(sizeof(person));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return 0;
	}

	while (P->next != NULL) {
		P = P->next;
	}

	q->name = name;
	q->surname = surname;
	q->year = year;
	q->next = P->next;
	P->next = q;
	return 0;
}

Pos Trazi(STRING sn, Pos P) {												//	<- Trazi
	while (P != NULL) {
		if (P->surname == sn) {
			return P;
		}
		P = P->next;
	}
	return NULL;
}

void Brisi(STRING sn, Pos P) {													//	<- Brisi
	Pos temp;

	while (P->next != NULL && P->next->surname != sn) {
		P = P->next;
	}
	if (P != NULL) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	else {
		printf("Person you wanted to remove is not in list,");

	}
}

int dodajIza(STRING afterThis, STRING nm, STRING sn, int yr, Pos P) {			// <- Dodaj Iza
	Pos q;

	while (P != NULL && P->surname != afterThis) {
		P = P->next;
	}

	q = (Pos)malloc(sizeof(person));
	if (q == NULL) {
		return 0;
	}
	
	q->name = nm;
	q->surname = sn;
	q->year = yr;
	q->next = P->next;
	P->next = q;
	return 0;
}

int dodajIspred(STRING beforeThis, STRING nm, STRING sn, int yr, Pos P) {		// <- Dodaj ispred
	Pos q;

	while (P->next != NULL && P->next->surname != beforeThis) {
		P = P->next;
	}

	q = (Pos)malloc(sizeof(person));
	if (q == NULL) {
		return 0;
	}
	q->name = nm;
	q->surname = sn;
	q->year = yr;
	q->next = P->next;
	P->next = q;
	return 0;
}

void sortiraj(Pos P) {											// <- sortiraj
	Pos temp, q;

	q = P;
	P = q->next;

	if (strcmp(P->surname, P->next->surname) > 0) {
		temp = P->next;
		q->next = temp;
		P->next = temp->next;
		temp->next = P;
		q = P;
		P = temp;
	}
	
}

void upisiudat(Pos P) {										// <- Upisi u datoteku
	FILE* fp;
	fp = fopen("podaci.txt", "w");

	while (P != NULL) {
		fprintf(fp, "%s\t%s\t%d\n", P->name, P->surname, P->year);
		P = P->next;
	}
	fclose(fp);
}


int izbrojiRetke(STRING filename) {								// <- broji retke
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}
	int br = 0;
	char line[256];

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (line[0] != '\n') {
			br++;
		}
	}
	fclose(fp);
	return br;
}

int citajIzdat(STRING filename, Pos P) {					// <- Citaj iz datoteke
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 0;
	}

	int br = izbrojiRetke(filename);
	if (br <= 0) {
		printf("Greska");
		fclose(fp);
		return 0;
	}

	for (int i = 0;i < br;i++) {
		STRING ime = malloc(25 * sizeof(char));
		if (ime == NULL) {
			printf("Greska pri alociranju imena - citajIzDat. ");
			return 0;
		}
		STRING prezime = malloc(25 * sizeof(char));
		if (prezime == NULL) {
			printf("Greska pri alociranju prezimena - citajIzDat.");
			return 0;
		}
		int godine;
		fscanf(fp, "%s %s %d", ime, prezime, &godine);
		unosKraj(ime, prezime, godine, P);
	}


	fclose(fp);
	return 0;
}
