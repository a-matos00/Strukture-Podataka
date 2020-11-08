#pragma once

typedef struct clan* p_clan;

typedef struct clan {
	int koef;
	int exp;
	p_clan next;

}_clan;

int ispis(p_clan p)
{
	if (p == NULL) {
		puts("Prazna lista!");
		return -1;
	}

	while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
	{
		if (p->next == NULL) {	//ako je zadnji clan u listi
			printf("%dx^%d", p->koef, p->exp);
		}

		else {	//opci slucaj
			printf("%dx^%d + ", p->koef, p->exp); //ispis podataka trenutnog clana liste
		}

		p = p->next;    //prebacujemo se na sljedeci clan u listi
	}

	puts("");

	return 0;
}

int sortiraniUnos(p_clan new_el, p_clan p)
{
	p_clan head = NULL;
	head = p;

	if (p->next == NULL) {
		new_el->next = p->next;
		p->next = new_el;
	}

	else {
		while (p->next != NULL && p->next->exp < new_el->exp) {
			p = p->next;
		}

		new_el->next = p->next;
		p->next = new_el;
	}
	p = head;

	return 0;
}

int ukloni(p_clan p)	//head element liste
{
	p_clan prev;
	
	p = p->next;

	while (p != NULL) {
		prev = p;
		p = p->next;

		free(prev);	
	}

	return 0;
}