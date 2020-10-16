#include<stdio.h>
#include<stdlib.h>

#define ERROR_1 (-1)	//ako datoteka nije otvorena

typedef struct student {	//definirana je nova vrsta podatka "_student"
	char ime[30];
	char prezime[30];
	int bodovi;
}_student;

int main()
{
	FILE* fp = NULL;	//pokazivac na datoteku
	_student* studenti;	//pokazivac na tip strukture 
	int n = 0;	//broj studenata
	int i = 0;

	fp = fopen("studenti.txt", "r");	//otvaramo datoteku

	if (fp == NULL) {	//ako datoteka nije otvorena 
		puts("GRESKA! Datoteka nije otvorena");
		return ERROR_1;
	}
	
	//sljedeca petlja broji retke jer je datoteka formatirana na nacin 1 redak = 1 student
	while (!feof(fp)) {
		if (fgetc(fp) == '\n')	//treba pripaziti na to da nakon broja bodova zadnjeg studenta u datoteci mora bit stisnut "enter"
			n++;
	}
	//printf("Broj studenata je %d\n",n); //provjera brojaca studenata

	rewind(fp);	//pokazivac se vraca na pocetak datoteke

	studenti = (_student*)malloc(sizeof(_student) * n);	//dinamicka alokacija niza struktura tipa _student

	//sljedeca petlja pohranjuje podatke studenata u strukture
	i = 0;	//jako je bitno da je i = 0 prije izvrsavanja petlje
	while (!feof(fp)) {	
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);	//skeniramo cijeli redak
		i++;
	}

	for (i = 0; i < n; i++) {
		printf("%s %s %d\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
	}

	fclose(fp);	//zatvaramo datoteku
}
