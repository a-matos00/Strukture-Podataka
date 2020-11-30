#pragma once

typedef struct el* p_el;

typedef struct el {
	int broj;
	p_el next;
}_el;

p_el alocNoviEl()
{
	p_el novi = (p_el)malloc(sizeof(_el));

	if (novi == NULL) {
		puts("MEMORY ERROR!");
		return NULL;
	}

	return novi;
}

int unosPrvogEl(p_el head, p_el novi)
{
	novi->next = head->next;
	head->next = novi;

	return 0;
}



int ispis(p_el p)
{
	p = p->next;

	while (p != NULL)
	{
		printf("%d ", p->broj);
		p = p->next;
	}
}

int sortiraniUnos(p_el p, p_el novi)
{
	
	if (p->next == NULL) {
		novi->next = p->next;
		p->next = novi;
	}

	else {
		while (p->next != NULL && p->next->broj < novi->broj) {
			p = p->next;
		}

		novi->next = p->next;
		p->next = novi;
	}

	return 0;
}

int generirajRand() {

	int x;  // "x" generirani nasumicni broj koji vracamo
	int i = 0;

	x = rand() % (10 - 1 + 1) + 1;   // "(b - a + 1) + a" za interval od <a,b>

	return x;

}

int unosKraj(p_el p, p_el novi)
{
	while (p->next != NULL) {
		p = p->next;
	}
	novi->next = p->next;
	p->next = novi;

	return 0;
}