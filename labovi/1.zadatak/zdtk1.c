#include<stdio.h>
#include<stdlib.h>

#define MAX_BOD (float)150	//najveci moguci broj bodova

typedef struct student {	//definirana je nova vrsta podatka "_student"
	char ime[30];
	char prezime[30];
	int bodovi;
	float rel_bodovi;
}_student;

int brojacStudenata(FILE*);	//funkcija vraca broj studenata
_student* alocirajNiz(_student*, int);
void ispis(_student*, int);
void upis(FILE*, _student*, int);
void relBod(_student*, int);

int main()
{
	FILE* fp = NULL;	//pokazivac na datoteku
	_student* studenti = NULL;	//pokazivac na tip strukture 
	int n = 0;	//broj studenata
	int i = 0, j = 0;	//iteratori

	fp = fopen("studenti.txt", "r");	//otvaramo datoteku

	if (fp == NULL) {	//ako datoteka nije otvorena 
		puts("GRESKA! Datoteka nije otvorena");
		return -1;
	}

	n = brojacStudenata(fp);	//funkcija vraca broj studenata

	rewind(fp);	//cursor se vraca na pocetak datoteke

	studenti = alocirajNiz(studenti, n);	//dinamicka alokacija niza struktura tipa _student

	upis(fp, studenti, n);	//prijenos podataka iz datoteke u niz struktura
	
	relBod(studenti, n);	//funkcija racuna relativne bodove studenata

	ispis(studenti, n);	//ispis cijelog niza struktura

	fclose(fp);	//zatvaramo datoteku
}

//sljedeca petlja broji retke jer je datoteka formatirana na nacin 1 redak = 1 student
int brojacStudenata(FILE* fp) {

	int n = 0;

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')	//treba pripaziti na to da nakon broja bodova zadnjeg studenta u datoteci mora bit stisnut "enter"
			n++;
	}

	return n;
}

_student* alocirajNiz(_student* p, int n) {

	p = (_student*)malloc(sizeof(_student) * n);

	if (p == NULL) {
		puts("Greška! Memorija nije alocirana");
		return NULL;
	}

	return p;
}

void upis(FILE* fp, _student* p, int n)
{
	int i = 0;	
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", p[i].ime, p[i].prezime, &p[i].bodovi);	//skeniramo cijeli redak
		i++;
	}
}

void relBod(_student* p, int n) {
	int i = 0;

	for (i = 0; i < n; i++) {
		p[i].rel_bodovi = (p[i].bodovi / MAX_BOD) * 100;
	}
}

void ispis(_student* p, int n)
{
	int i = 0;

	for (i = 0; i < n; i++) {
		printf("%s %s %d %.2f\n", p[i].ime, p[i].prezime, p[i].bodovi, p[i].rel_bodovi);
	}
}
