#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define max_bodovi 80.0

typedef struct Student {
	char ime[50];
	char prezime[50];
	int bodovi;
}stud;

int izbrojiRetke(char* filename) {
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


stud* upisaniStudenti(char* filename, int brRed) {
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}
	stud *studenti = malloc(brRed * sizeof(stud));
	if (studenti == NULL) {
		printf("Greska pri ucitavanju studenta.");
		return 1;
	}

	for (int i = 0;i < brRed;i++) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}
	
	fclose(fp);
	return studenti;	
}

void ispis(stud* studenti, int brRed) {
	printf("Ime\tPrezime\t\tBodovi\tRelativni bodovi\n");
	printf("----------------------------------------------------\n");
	for (int i = 0;i < brRed;i++) {
		double relativni = (double)studenti[i].bodovi / max_bodovi * 100.0;
		printf("%s\t%s\t\t%d\t%.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);
	}
}



int main() {
	char* datoteka = "podaci.txt";
	int br = izbrojiRetke(datoteka);
	stud *studenti = upisaniStudenti(datoteka, br);
	ispis(studenti, br);
	return 0;
}