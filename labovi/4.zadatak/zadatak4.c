#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"	//struktura, ispis, sortiranje, ukloni listu

int citajIzDat(FILE*, p_clan, p_clan);
int ispis(p_clan);	//ispis liste polinoma
int bufferSize(FILE*);	//izracun velicine buffera
int ucitajPol(char*, p_clan, p_clan);
int sortiraniUnos(p_clan);	//sortirani unos u listu
int zbrojiPol(p_clan, p_clan, p_clan);
int mnoziPol(p_clan, p_clan, p_clan);
int zbrIsteExp(p_clan);	//zbraja sve clanove polinoma sa istim eksponentom
int ukloni(p_clan);	//funkcija uklanja listu iz memorije

int main()
{
	FILE* fp;

	_clan p1_HEAD, p2_HEAD, rez_HEAD;	//prvi pol, drugi pol, rezultatni pol

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

	zbrIsteExp(&rez_HEAD);
	printf("Ispis konacnog rezultata: ");
	ispis(rez_HEAD.next);

	//oslobadanje memorije
	ukloni(&p1_HEAD);
	ukloni(&p2_HEAD);
	ukloni(&rez_HEAD);

	return 0;
}

int mnoziPol(p_clan p1, p_clan p2, p_clan rez)
{
	p_clan new_el, rez_HEAD, p2_start;

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
			new_el = (p_clan)malloc(sizeof(_clan));

			new_el->exp = (p1->exp + p2->exp);	//unos podataka
			new_el->koef = (p1->koef * p2->koef);

			sortiraniUnos(new_el, rez_HEAD);

			p2 = p2->next;
		}
		
		p1 = p1->next;
		p2 = p2_start;
	}

	return 0;
}

int zbrIsteExp(p_clan p_HEAD)
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
			fol = fol->next;	//new_el sljedeci element
			prev = prev;	//prethodni ostaje isti
		}
		else {
			prev = curr;	//trenutni postaje prethodni
			curr = fol;	//new_el trenutni
			fol = fol->next; //new_el sljedeci
		}
	}
	return 0;
}

int citajIzDat(FILE* fp, p_clan p1, p_clan p2)
{
	int buffer_size = 0;
	p_clan new_el = NULL;
	char* buffer = NULL;
	int offset = 0, exp = 0, koef = 0, r = 0;	//pomocne varijable

	buffer_size = bufferSize(fp);	//odredujemo velicinu buffera

	buffer = (char*)calloc(buffer_size, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, buffer_size, 1, fp);	//sadrzaj datoteke se upisuje u buffer

	fclose(fp);

	printf("ISPIS BUFFERA:\n%s\n", buffer);	//provjera sadrzaja buffera

	//funkcija vraca pomak pokazivaca u stringu nakon citanja prvog polinoma
	offset = ucitajPol(buffer, p1, new_el);	//prvi polinom se upisuje u listu	

	buffer = (buffer + offset);	//pomice se pokazivac buffera

	ucitajPol(buffer, p2, new_el);	//ucitavanje drugog polinoma u listu

	return 0;
}

int bufferSize(FILE* fp) {	//racuna se velicina buffera
	int buffer_size = 0;
	
	fseek(fp, 0, SEEK_END);	//stavljam file pointer na kraj
	buffer_size = ftell(fp);	// funkcija vraca kolicinu bajtova od pocetka do trenutne pozicije
	rewind(fp);	//pokazivac datoteke se vraca na pocetak

	printf("DULJINA BUFFERA JE %d\n", buffer_size);	//provjera

	return buffer_size;
}

int ucitajPol(char* buffer, p_clan p, p_clan new_el)
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
		

		new_el = (p_clan)malloc(sizeof(_clan)); //stvaramo novu strukturu

		new_el->koef = koef;	//unos podataka u new_el clan
		new_el->exp = exp;

		sortiraniUnos(new_el, p);

		if (*buffer == '\n') {	//ako smo ucitali cijeli prvi redak("polinom")
			break;
		}

	}

	offset += 1;	//kod cita 1 offset viska

	return offset;
}


int zbrojiPol(p_clan p1, p_clan p2, p_clan rez) {
	p_clan new_el, rez_HEAD;

	rez_HEAD = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->exp < p2->exp) {
			new_el = (p_clan)malloc(sizeof(_clan));	//stvara se new_el clan

			new_el->exp = p1->exp;	//unos podataka
			new_el->koef = p1->koef;

			new_el->next = rez->next;	//dodaje se u listu
			rez->next = new_el;

			p1 = p1->next;

			rez = rez->next;
		}

		else if (p1->exp > p2->exp) {
			new_el = (p_clan)malloc(sizeof(_clan));	//stvara se new_el clan

			new_el->exp = p2->exp;	//unos podataka
			new_el->koef = p2->koef;

			new_el->next = rez->next;	//dodaje se u listu
			rez->next = new_el;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->exp == p2->exp) {
			new_el = (p_clan)malloc(sizeof(_clan));	//stvara se new_el clan

			new_el->exp = p2->exp;	//unos podataka
			new_el->koef = p2->koef + p1->koef;

			new_el->next = rez->next;	//dodaje se u listu
			rez->next = new_el;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}
		
	}

	//SLIJEDE SLUCAJEVI AKO SMO DOSLI DO KRAJA JEDNOG ILI DRUGOG POLINOMA
	//tada samo na kraj liste unosimo preostale clanove polinoma jer su sortirani vec

	if (p1 != NULL) {
		while (p1 != NULL) {
			new_el = (p_clan)malloc(sizeof(_clan));

			new_el->koef = p1->koef;
			new_el->exp = p1->exp;

			new_el->next = rez->next;	//dodaje se u listu
			rez->next = new_el;

			p1 = p1->next;
			rez = rez->next;
		}

	}

	if (p2 != NULL) {
		while (p2 != NULL) {
			new_el = (p_clan)malloc(sizeof(_clan));

			new_el->koef = p2->koef;
			new_el->exp = p2->exp;

			new_el->next = rez->next;	//dodaje se u listu
			rez->next = new_el;

			p2 = p2->next;
			rez = rez->next;
		}

	}

	return 0;
}

