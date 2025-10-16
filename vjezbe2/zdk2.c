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


int main() {															//	<- main
	person Head = { NULL, NULL, 0, NULL};
	unosPocetak("Ivo", "Zelic", 2005, &Head);
	unosPocetak("Sime", "Zec", 2005, &Head);
	unosKraj("Ante", "Poljak", 2005, &Head);
	unosKraj("Mate", "Simic", 2004, &Head);
	ispis(&Head);

	if (Trazi("Zelic", &Head) == NULL) {
		printf("Person is not in list.");
	}
	else {
		printf("Person is in list.\n");
	}
	
	Brisi("Zelic", &Head);
	printf("--------------------------------------\n");
	ispis(&Head);

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
