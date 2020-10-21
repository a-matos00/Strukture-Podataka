#include<stdio.h>
#include<stdlib.h>

#define ERROR_1 (-1)	//ako datoteka nije otvorena

typedef struct student {	//definirana je nova vrsta podatka "_student"
	char ime[30];
	char prezime[30];
	int bodovi;
	float rel_bodovi;
}_student;

float max_bodovi(_student*, int);	//funkcija trazi i vraca najveci broj bodova
int brojac_studenata(FILE*);	//funkcija vraca broj studenata

int main()
{
	FILE* fp = NULL;	//pokazivac na datoteku
	_student* studenti;	//pokazivac na tip strukture 
	int n = 0;	//broj studenata
	int i = 0, j = 0;
	float temp = 0;
	float max_bod = 0;	//maksimalni postignuti broj bodova od svih studenata

	fp = fopen("studenti.txt", "r");	//otvaramo datoteku

	if (fp == NULL) {	//ako datoteka nije otvorena 
		puts("GRESKA! Datoteka nije otvorena");
		return ERROR_1;
	}

	n = brojac_studenata(fp);	//funkcija vraca broj studenata
	
	//printf("Broj studenata je %d\n",n); //provjera brojaca studenata

	rewind(fp);	//pokazivac se vraca na pocetak datoteke

	studenti = (_student*)malloc(sizeof(_student) * n);	//dinamicka alokacija niza struktura tipa _student

	//sljedeca petlja pohranjuje podatke studenata u strukture
	i = 0;	//jako je bitno da je i = 0 prije izvrsavanja petlje
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);	//skeniramo cijeli redak
		i++;
	}

	max_bod = max_bodovi(studenti, n);	//pozivamo funkciju koja vraca najveci broj bodova

	for (i = 0; i < n; i++) {
		studenti[i].rel_bodovi = (studenti[i].bodovi / max_bod) * 100;
	}

	for (i = 0; i < n; i++) {
		printf("%s %s %d %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, studenti[i].rel_bodovi);
	}

	fclose(fp);	//zatvaramo datoteku
}

float max_bodovi(_student* p, int n)
{
	float max_bod = p[0].bodovi;
	int i = 0;

	for (i = 0; i < n - 1; i++)
		if (p[i].bodovi > p[i + 1].bodovi) {
			max_bod = p[i].bodovi;
		}

	return max_bod;
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
