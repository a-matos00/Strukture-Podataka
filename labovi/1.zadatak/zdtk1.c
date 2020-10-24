#include<stdio.h>
#include<stdlib.h>

#define MAX_BOD (float)150	//najveci moguci broj bodova

typedef struct student {	//definirana je nova vrsta podatka "_student"
	char ime[30];
	char prezime[30];
	int bodovi;
	float rel_bodovi;
}_student;

int brojac_studenata(FILE*);	//funkcija vraca broj studenata

int main()
{
	FILE* fp = NULL;	//pokazivac na datoteku
	_student* studenti;	//pokazivac na tip strukture 
	int n = 0;	//broj studenata
	int i = 0, j = 0;	//iteratori

	fp = fopen("studenti.txt", "r");	//otvaramo datoteku

	if (fp == NULL) {	//ako datoteka nije otvorena 
		puts("GRESKA! Datoteka nije otvorena");
		return -1;
	}

	n = brojac_studenata(fp);	//funkcija vraca broj studenata

	rewind(fp);	//cursor se vraca na pocetak datoteke

	studenti = (_student*)malloc(sizeof(_student) * n);	//dinamicka alokacija niza struktura tipa _student

	//sljedeca petlja pohranjuje podatke studenata u strukture
	i = 0;	//jako je bitno da je i = 0 prije izvrsavanja petlje
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);	//skeniramo cijeli redak
		i++;
	}

	for (i = 0; i < n; i++) {
		studenti[i].rel_bodovi = (studenti[i].bodovi / MAX_BOD) * 100;
	}

	for (i = 0; i < n; i++) {
		printf("%s %s %d %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, studenti[i].rel_bodovi);
	}

	fclose(fp);	//zatvaramo datoteku
}

//sljedeca petlja broji retke jer je datoteka formatirana na nacin 1 redak = 1 student
int brojac_studenata(FILE* fp) {

	int n = 0;

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')	//treba pripaziti na to da nakon broja bodova zadnjeg studenta u datoteci mora bit stisnut "enter"
			n++;
	}

	return n;
}
