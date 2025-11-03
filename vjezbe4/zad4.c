#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef char* STRING;
typedef struct polinom* Pos;
typedef struct polinom {
	int coef;
	int power;
	Pos* next;
}poly;


int add_to_poly(int, int, Pos);
void printing(Pos);
int input(FILE*, Pos);
poly add(Pos, Pos);
poly multiply(Pos, Pos);

int main() {
	poly Head = {0, 0, NULL};
	poly firstPoly = Head;
	poly secondPoly = Head;
	Pos q = &Head;

	FILE* fp;
	fp = fopen("podaci.txt", "r");
	if (fp == NULL) {
		printf("Error when loading file.");
		return 0;
	}

	input(fp, &firstPoly);
	input(fp, &secondPoly);
	

	printf("First poly:\n");
	printing(firstPoly.next);
	printf("Second poly:\n");
	printing(secondPoly.next);
	poly sum = add(firstPoly.next, secondPoly.next);
	printf("Sum of 2 poly is: \n");
	printing(sum.next);
	
	fclose(fp);
	return 0;
}

int add_to_poly(int c, int pow, Pos P) {
	Pos q, temp;
	temp = P->next;

	q = (Pos)malloc(sizeof(poly));
	if (q == NULL) {
		printf("Errow while malloc.");
		return 0;
	}
	if (P == NULL) {					//provjera jeli lista (polinom) prazna, dodavanje prvog elementa u listi
		q->coef = c;
		q->power = pow;
		q->next = P->next;
		P->next = q;
		return 0;
	}
	
	while (P->next != 0 && temp->power > pow) {
		P = P->next;
		temp = temp->next;
	}
	if (temp != NULL && temp->power == pow) {			//provjera jeli postoji vec taj power
		temp->coef += c;
		if (temp->coef == 0) {				//brisanje ako je coef = 0
			P->next = temp->next;
			free(temp);
			return 0;						
		}									
		return 0;		
	}										
	
	q->coef = c;							
	q->power = pow;
	q->next = P->next;
	P->next = q;
}

void printing(Pos P) {
	if (P == NULL) {
		printf("Error while printing");
	}
	while (P != NULL) {
		printf("%d %d\t", P->coef, P->power);
		P = P->next;
	}
	printf("\n");
}


int input(FILE* fp, Pos P) {

	char buffer[256];
	fgets(buffer, sizeof(buffer), fp);

	int c, pow, consumed;

	STRING p_buffer = &buffer;
	while (sscanf(p_buffer, "%d %d %n", &c, &pow, &consumed) == 2) {		
		add_to_poly(c, pow, P);
		printf("Procitao: coef: %d\tpower: %d\tconsumed: %d\n", c, pow, consumed);
		p_buffer += consumed;
	}
	return 0;
}

poly add(Pos first, Pos second) {
	poly q = { 0, 0, NULL };
	
	while (first != NULL) {
		add_to_poly(first->coef, first->power, &q);
		first = first->next;
	}
	while (second != NULL) {
		add_to_poly(second->coef, second->power, &q);
		second = second->next;
	}

	return q;
}

poly multiply(Pos first, Pos second) {


}