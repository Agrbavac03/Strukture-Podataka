#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char* STRING;

typedef struct Item* PosI;
typedef struct Item {
	char name[64];
	int quantity;
	double price;
	PosI next;
}Item;

typedef struct bill* PosR;
typedef struct bill {
	int year, month, day;
	PosI HeadItem;
	PosR next;
}bill;


int loadAllBills(STRING, PosR);
int loadOneBill(STRING, PosR);
void printAll(PosR);
int findRequest(PosR);
int sortedInsertItem(PosI*, PosI);
int sortedByDate(PosR, PosR);
int dateCompare(int, int, int, int, int, int);


int main() {
	bill Head = { 0 };
	Head.HeadItem = NULL;
	Head.next = NULL;
	
	STRING data = "racuni.txt";

	loadAllBills(data, &Head);

	printAll(&Head);

	findRequest(&Head);
	return 0;
}


int loadAllBills(STRING filename, PosR P) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska Pri ucitavanja datoteke");
		return 0;
	}

	char oneLine[256];

	while (fscanf(fp, "%s", oneLine) == 1) {		//red po red iz billi.txt
		printf("%s\n", oneLine);
		loadOneBill(oneLine, P);
	}

	fclose(fp);
	return 1;
}

int loadOneBill(STRING line, PosR P) {
	FILE* fp = fopen(line, "r");
	if (fp == NULL) {								//provjera postoji li txt s tim nameom
		printf("Greska pri ucitavanju datoteke\n");
		return 0;
	}

	char buffer[256];

	if (fgets(buffer, sizeof(buffer), fp) == 0) {	//ako je txt prazna datoteka
		printf("Datoteka je prazna\n");
		fclose(fp);
		return 0;
	}

	int y, m, d;
	if (sscanf(buffer, "%d-%d-%d", &y, &m, &d) != 3) {	//provjera formata i spremanje linije u buffer
		printf("Neispravan format - datum\n");
		fclose(fp);
		return 0;
	}

	PosR new;
	new = malloc(sizeof(bill));						//novi bill na koji spremamo podatke (datum)
	if (!new) {
		printf("Greska pri alociranju memorije - new\n");
		fclose(fp);
		return 0;
	}

	new->year = y;
	new->month = m;
	new->day = d;
	new->HeadItem = NULL;
	new->next = NULL;

	while (fgets(buffer, sizeof(buffer), fp)) {		//dok postoji buffer, dok nije prazan
		PosI item;
		item = malloc(sizeof(Item));				//item koji koristimo za spremanje podataka, jednog po jednog iz datoteke
		if (!item) {
			printf("Greska pri alokaciji memorije - item\n");
			fclose(fp);
		}
		item->next = NULL;
		
		if (sscanf(buffer, " %63[^,], %d, %lf", item->name, &item->quantity, &item->price) == 3) {	//scan i formatiranje buffera
			sortedInsertItem(&new->HeadItem, item);
		}
		else {
			printf("Neispravan format - item u listi\n");
			free(item);
		}
	}
	fclose(fp);


	sortedByDate(P, new);	//new je onaj bill kod kojeg smo spremali datum, sada njega sortiramo
	return 1;
}

int sortedInsertItem(PosI* Head, PosI novi) {	
	if (*Head == NULL || strcmp(novi->name, (*Head)->name) < 0) {	//ako je ovo prvi element u listi tog datuma ili ako je novi manji od prvog
		novi->next = *Head;											//onda se sprema kao head, prvi element, pocetak cvora
		*Head = novi;			
		return 1;
	}

	PosI current = *Head;
	while ((current->next != NULL) && strcmp(current->next->name, novi->name) < 0) {		//dok ne dodemo do manjeg namea
		current = current->next;
	}

	novi->next = current->next;
	current->next = novi;
	return 1;
}

int sortedByDate(PosR P, PosR novi) {		//P je head (pocetak svega) i novi bill kojem trazimo mjesto
	PosR prev = P;
	PosR current = P->next;

	while (current != NULL && (dateCompare(current->year, current->month, current->day, novi->year, novi->month, novi->day) < 0)) {
		prev = current;
		current = current->next;
	}
	printf("Novi se ubacuje nakon %d-%d-%d, a to je - %d-%d-%d\n", prev->day, prev->month, prev->year, novi->day, novi->month, novi->year);
	novi->next = current;
	prev->next = novi;
}


int dateCompare(int y1, int m1, int d1, int y2, int m2, int d2) {		//usporedba datuma, <0 ako je "1" veci od "2", >0 ako je "1" manji od "2"
	if (y1 != y2) return y1 - y2;		//ako je 1. veci od 2. vraca 1
	if (m1 != m2) return m1 - m2;
	return d1 - d2;
}

void printAll(PosR P) {
	PosR temp = P->next;

	while (temp != NULL) {
		printf("\nbill datum: %d-%d-%d\n", temp->day, temp->month, temp->year);	
		printf("Artikli:\n");

		//prolaz kroz listu jednog billa
		PosI a = temp->HeadItem;				//a je trenutni head element svakog billa, cvor izmedu 2 strukture

		while (a != NULL) {
			printf(" %-20s  x%d price: %.2f  ukupno: %.2f\n",
				a->name, a->quantity, a->price, a->price * a->quantity);
			a = a->next;
		}

		temp = temp->next;
	}
}

int findRequest(PosR P) {
	char requested[64];
	char fromDate[16], toDate[16];
	int y1, m1, d1;
	int y2, m2, d2;

	printf("Enter name of item you want to find: ");			//Unos parametara
	scanf("%63s", requested);

	printf("Enter starting date: ");
	scanf("%15s", fromDate);
	printf("Enter final date: ");
	scanf("%15s", toDate);

	if (sscanf(fromDate, "%d-%d-%d", &d1, &m1, &y1) != 3 ||
		sscanf(toDate, "%d-%d-%d", &d2, &m2, &y2) != 3) {
		printf("Incorrect input od date!\n");
		return 0;
	}

	double totalMoney = 0.0;
	int totalQty = 0;

	PosR q = P->next;

	while (q != NULL) {
		if (dateCompare(q->year, q->month, q->day, y1, m1, d1) >= 0 &&			//Provjera nalazili se u zadanom rasponu datuma
			dateCompare(q->year, q->month, q->day, y2, m2, d2) <= 0) {
			PosI temp = q->HeadItem;
				while (temp != NULL) {
					if (strcmp(temp->name, requested) == 0) {
						totalQty += temp->quantity;
						totalMoney += temp->quantity * temp->price;
					}
					temp = temp->next;
				}
		}	
		q = q->next;
	}

	printf("\nItem %s from %s - %s:\n", requested, fromDate, toDate);
	printf("  Total quantity: %d\n", totalQty);
	printf("  Total money: %.2f\n", totalMoney);
	return 1;
}