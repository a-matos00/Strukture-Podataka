#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"

int CitajIzDat(FILE*, p_clan, p_clan);
int ispis(p_clan);
int bufferSize(FILE*);
int ucitajPol(char*, p_clan, p_clan);
int sortiraniUnos(p_clan);
int zbrojiPol(p_clan, p_clan, p_clan);

int main()
{
	FILE* fp;

	_clan p1_HEAD, p2_HEAD, rez_HEAD;

	p1_HEAD.next = NULL;
	p2_HEAD.next = NULL;
	rez_HEAD.next = NULL;

	fp = fopen("datoteka.txt", "r");

	if (fp == NULL) {
		puts("DATOTEKA NIJE OTVORENA");
		return -1;
	}

	CitajIzDat(fp, &p1_HEAD, &p2_HEAD);

	printf("Ispis prvog polinoma: ");
	ispis(p1_HEAD.next);

	printf("Ispis drugog polinoma: ");
	ispis(p2_HEAD.next);

	
	zbrojiPol(p1_HEAD.next, p2_HEAD.next, &rez_HEAD);

	printf("Ispis zbroja: ");
	ispis(rez_HEAD.next);

	return 0;
}



int izDat(FILE* fp, p_clan p1, p_clan p2)
{
	int buffer_size = 0;
	p_clan novi = NULL;
	char* buffer = NULL;
	int offset = 0, exp = 0, koef = 0, r = 0;

	buffer_size = bufferSize(fp);

	buffer = (char*)calloc(buffer_size, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, buffer_size, 1, fp);

	//printf("DULJINA BUFFERA JE %d\n", strlen(buffer)); //provjera duljine buffera
	printf("ISPIS BUFFERA:\n %s\n", buffer);	//PROVJERA BUFFERA

	offset = ucitajPol(buffer, p1, novi);

	buffer = (buffer + offset);

	ucitajPol(buffer, p2, novi);

	rewind(fp);

	return 0;
}

int bufferSize(FILE* fp) {
	int buffer_size = 0;
	
	fseek(fp, 0, SEEK_END);	//stavljam file pointer na kraj
	buffer_size = ftell(fp);	// funkcija vraca kolicinu bajtova od pocetka do trenutne pozicije
	rewind(fp);

	printf("DULJINA BUFFERA JE %d\n", buffer_size);

	return buffer_size;
}

int ucitajPol(char* buffer, p_clan p, p_clan novi)
{
	int koef, exp, n, r;
	int offset = 0;
	p_clan head = p;

	while (buffer != EOF) {
		r = sscanf(buffer, "%dx^%d +%n", &koef, &exp, &n);

		if (r == EOF) {
			puts("GRESKA U CITANJU");
			return -1;
		}

		if (r == 0) {	// procitan redak
			break;
		}

		offset += n;

		buffer = (buffer + n);	//pomicemo pokazivac buffera na ono mjesto do kojeg smo obavili sscanf

		novi = (p_clan)malloc(sizeof(_clan)); //stvaramo novu strukturu

		novi->koef = koef;	//unos podataka u novi clan
		novi->exp = exp;

		sortiraniUnos(novi, p);

	}

	offset -= 1;	//kod cita 1 offset viska

	return offset;
}



int zbrojiPol(p_clan p1, p_clan p2, p_clan rez) {
	p_clan novi;

	while (p1 != NULL && p2 != NULL) {
		if (p1->exp < p2->exp) {
			novi = (p_clan)malloc(sizeof(_clan));	//stvara se novi clan

			novi->exp = p1->exp;	//unos podataka
			novi->koef = p1->koef;

			novi->next = rez->next;	//dodaje se u listu
			rez->next = novi;

			p1 = p1->next;

			rez = rez->next;
		}

		else if (p1->exp > p2->exp) {
			novi = (p_clan)malloc(sizeof(_clan));	//stvara se novi clan

			novi->exp = p2->exp;	//unos podataka
			novi->koef = p2->koef;

			novi->next = rez->next;	//dodaje se u listu
			rez->next = novi;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->exp == p2->exp) {
			novi = (p_clan)malloc(sizeof(_clan));	//stvara se novi clan

			novi->exp = p2->exp;	//unos podataka
			novi->koef = p2->koef + p1->koef;

			novi->next = rez->next;	//dodaje se u listu
			rez->next = novi;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}
		
	}

	if (p1 != NULL) {
		while (p1 != NULL) {
			novi = (p_clan)malloc(sizeof(_clan));

			novi->koef = p1->koef;
			novi->exp = p1->exp;

			novi->next = rez->next;	//dodaje se u listu
			rez->next = novi;

			p1 = p1->next;
			rez = rez->next;
		}

	}

	if (p2 != NULL) {
		while (p2 != NULL) {
			novi = (p_clan)malloc(sizeof(_clan));

			novi->koef = p2->koef;
			novi->exp = p2->exp;

			novi->next = rez->next;	//dodaje se u listu
			rez->next = novi;

			p2 = p2->next;
			rez = rez->next;
		}

	}


	return 0;
}