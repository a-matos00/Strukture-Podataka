#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"

int citajIzDat(FILE*, p_clan, p_clan);
int ispis(p_clan);
int bufferSize(FILE*);
int ucitajPol(char*, p_clan, p_clan);
int sortiraniUnos(p_clan);
int zbrojiPol(p_clan, p_clan, p_clan);
int mnoziPol(p_clan, p_clan, p_clan);
int srediPol(p_clan);

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

	citajIzDat(fp, &p1_HEAD, &p2_HEAD);

	printf("Ispis prvog polinoma: ");
	ispis(p1_HEAD.next);

	printf("Ispis drugog polinoma: ");
	ispis(p2_HEAD.next);

	//zakomentirat oni koji se ne koristi
	//zbrojiPol(p1_HEAD.next, p2_HEAD.next, &rez_HEAD);
	mnoziPol(p1_HEAD.next, p2_HEAD.next, &rez_HEAD);
	printf("Ispis prije sredivanja: ");
	ispis(rez_HEAD.next);

	srediPol(&rez_HEAD);
	printf("Ispis konacnog rezultata: ");
	ispis(rez_HEAD.next);

	return 0;
}

int mnoziPol(p_clan p1, p_clan p2, p_clan rez)
{
	p_clan novi, rez_HEAD, p2_start;

	rez_HEAD = rez;
	p2_start = p2;
	

	if (p1 == NULL || p2 == NULL || rez == NULL) {	//provjera
		puts("GREŠKA! Jedan od pokazivaca na polinom je NULL");
		return -1;
	}

	while (p1 != NULL)
	{

		while (p2 != NULL)
		{
			novi = (p_clan)malloc(sizeof(_clan));

			novi->exp = (p1->exp + p2->exp);	//unos podataka
			novi->koef = (p1->koef * p2->koef);

			sortiraniUnos(novi, rez_HEAD);

			p2 = p2->next;
		}
		
		p1 = p1->next;
		p2 = p2_start;
	}

	return 0;
}

int srediPol(p_clan p_HEAD)
{
	p_clan prev, curr, fol;	//prethodni, trenutni, sljedeci

	prev = p_HEAD;
	curr = p_HEAD->next;
	fol = curr->next;

	while (fol != NULL)
	{
		if (curr->exp == fol->exp) {	//ako su eksponenti jednaki
			fol->koef += curr->koef;	//zbroj koef unosimo u sljedeci

			prev->next = fol;	//trenutni se iskljucuje iz liste
			free(curr);	//oslobada se memorija trenutnog

			curr = fol;	//sljedeci postaje trenutni
			fol = fol->next;	//novi sljedeci element
			prev = prev;	//prethodni ostaje isti
		}
		else {
			prev = curr;	//trenutni postaje prethodni
			curr = fol;	//novi trenutni
			fol = fol->next; //novi sljedeci
		}
	}
	return 0;
}

int citajIzDat(FILE* fp, p_clan p1, p_clan p2)
{
	int buffer_size = 0;
	p_clan novi = NULL;
	char* buffer = NULL;
	int offset = 0, exp = 0, koef = 0, r = 0;

	buffer_size = bufferSize(fp);

	buffer = (char*)calloc(buffer_size, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, buffer_size, 1, fp);	//tekst se upisuje u buffer

	fclose(fp);
	//printf("DULJINA BUFFERA JE %d\n", strlen(buffer)); //provjera duljine buffera
	printf("ISPIS BUFFERA:\n%s\n", buffer);	//PROVJERA BUFFERA

	offset = ucitajPol(buffer, p1, novi);

	buffer = (buffer + offset);

	ucitajPol(buffer, p2, novi);

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
	int offset = 0;	//pomak u stringu
	p_clan head = p;

	while (buffer != EOF) {
		r = sscanf(buffer, "%d %d%n", &koef, &exp, &n);

		if (r == EOF) {		//kraj datoteke
			puts("KRAJ DATOTEKE");
			return -1;
		}

		if (r == 0) {	//nije u formatu
			puts("POGRESAN FORMAT");
			break;
		}

		offset += n;

		buffer = (buffer + n);	//pomicemo pokazivac buffera na ono mjesto do kojeg smo obavili sscanf
		

		novi = (p_clan)malloc(sizeof(_clan)); //stvaramo novu strukturu

		novi->koef = koef;	//unos podataka u novi clan
		novi->exp = exp;

		sortiraniUnos(novi, p);

		if (*buffer == '\n') {	//ako smo ucitali cijeli prvi redak("polinom")
			break;
		}

	}

	offset += 1;	//kod cita 1 offset viska

	return offset;
}


int zbrojiPol(p_clan p1, p_clan p2, p_clan rez) {
	p_clan novi, rez_HEAD;

	rez_HEAD = rez;

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

