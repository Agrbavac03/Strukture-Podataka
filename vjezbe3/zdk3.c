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
void unosKraj(STRING, STRING, int, Pos);
Pos Trazi(STRING, Pos);
void Brisi(STRING, Pos);
void dodajIza(STRING, STRING, STRING, int, Pos);
void dodajIspred(STRING, STRING, STRING, int, Pos);
void upisiudat(Pos);
void citajIzdat(STRING, Pos);



int main() {															//	<- main
	person Head = { NULL, NULL, 0, NULL };
	unosPocetak("Ivan", "Zelic", 2005, &Head);
	unosPocetak("Sime", "Zebic", 2005, &Head);
	unosKraj("Ante", "Poljak", 2005, &Head);
	unosKraj("Mate", "Simic", 2004, &Head);
	ispis(&Head);
	/*
	if (Trazi("Zelic", &Head) == NULL) {
		printf("Person is not in list.");
	}
	else {
		printf("Person is in list.\n");
	}

	Brisi("Zelic", &Head);*/
	printf("--------------------------------------\n");
	
	
	dodajIza("Poljak", "Luka", "Lemo", 2003, &Head);
	dodajIspred("Poljak", "Marin", "Lukic", 2001, &Head);
	ispis(&Head);
	upisiudat(Head.next);

	return 0;
}

int unosPocetak(STRING name, STRING surname, int year, Pos P) {			// <- unos na pocetak
	Pos q;
	q = (Pos)malloc(sizeof(person));

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

void unosKraj(STRING name, STRING surname, int year, Pos P) {			//	<- Unos na kraj
	Pos q;
	q = (Pos)malloc(sizeof(person));

	while (P->next != NULL) {
		P = P->next;
	}

	q->name = name;
	q->surname = surname;
	q->year = year;
	q->next = P->next;
	P->next = q;
}

Pos Trazi(STRING sn, Pos P) {											//	<- Trazi
	while (P != NULL) {
		if (P->surname == sn) {
			return P;
		}
		P = P->next;
	}
	return NULL;
}

void Brisi(STRING sn, Pos P) {											//	<- Brisi
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

void dodajIza(STRING afterThis, STRING nm, STRING sn, int yr, Pos P) {	 // <- Dodaj Iza
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
}

void dodajIspred(STRING beforeThis, STRING nm, STRING sn, int yr, Pos P) {		// <- Dodaj ispred
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
}

void sortiraj(Pos P) {
	person q = { NULL, NULL, 0, NULL };
	Pos temp;
	
	P = q->next;


	if (strcnp(P->surname, P->next->surname) > 0) {
		P = P->next;
		q = q->next;
		temp = P->next;
		q->next = temp;
		P->next = temp;
		temp->next = P;
		P = temp;
		q = P;
		P = P->next;
	}

	sorted = P
	
}

void upisiudat(Pos P) {										// <- Upisi u datoteku
	FILE* fp;
	fp = fopen("podaci.txt", "w");

	while (P != NULL) {
		fprintf(fp, "%s\t\%s\t%d\n", P->name, P->surname, P->year);
		P = P->next;
	}
}

void citajIzdat(STRING filename, Pos P) {					// <- Citaj iz datoteke
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 0;
	}

	char line[256];
	int br = 0;


	while (fgets(line, sizeof(line), fp) != NULL) {
		fscanf(fp, "%s %s %d");
		br++;
	}

	Pos q = malloc(br * sizeof(person));

	for (int i = 0;i < br;i++) {
		
	}
}
