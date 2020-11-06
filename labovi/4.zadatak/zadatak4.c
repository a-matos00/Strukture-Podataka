#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct clan* p_clan;

typedef struct clan {
	int koef;
	int exp;
	p_clan next;
}_clan;

int izDat(FILE*, p_clan);
int ispis(p_clan);
int bufferSize(FILE*);

int main()
{
	FILE* fp;

	_clan p1_HEAD;

	p1_HEAD.next = NULL;

	fp = fopen("datoteka.txt", "r");

	if (fp == NULL) {
		puts("DATOTEKA NIJE OTVORENA");
		return -1;
	}

	izDat(fp, &p1_HEAD);
	ispis(p1_HEAD.next);

	return 0;
}

int izDat(FILE* fp, p_clan p1_HEAD)
{
	p_clan p1;
	char* buffer;
	int n = 0, exp = 0, koef = 0,r = 0;
	
	buffer = (char*)malloc(bufferSize(fp));
	
	fgets(buffer, strlen(buffer), fp);

	rewind(fp);

	
		r = sscanf(buffer, "%d %d %n", &koef, &exp, &n);

		printf("koef = %d exp = %d n = %d ", koef, exp, n);

		if (r == EOF) {
			puts("GRESKA U CITANJU");
			return -1;
		}

		else if (r != EOF) {
			puts("SSCANF USPJESAN");
		}

		fseek(fp, n, SEEK_SET);

		p1 = (p_clan)malloc(sizeof(_clan)); //stvaramo novu strukturu

		p1->koef = koef;
		p1->exp = exp;

		p1->next = p1_HEAD->next;
		p1_HEAD->next = p1;
	
	rewind(fp);

	return 0;
}

int ispis(p_clan p)
{
	puts("ISPIS LISTE:");

	if (p == NULL) {
		puts("Prazna lista!");
		return -1;
	}

	while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
	{
		printf("%dx^%d", p->koef, p->exp); //ispis podataka trenutnog clana liste
		p = p->next;    //prebacujemo se na sljedeci clan u listi
	}

	return 0;
}

int bufferSize(FILE* fp) {
	int n = 0;

	while (!feof(fp)) {
		++n;	//brojac znakova
		fgetc(fp);
	}
	rewind(fp);

	printf("DULJINA BUFFERA JE %d\n", n);

	return n;
}

