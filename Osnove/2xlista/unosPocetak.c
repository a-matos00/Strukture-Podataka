#include<stdio.h>

typedef struct el* p_el;

typedef struct el{
	int broj;
	p_el next;
	p_el prev;
}_el;			//tip strukture _el

int dodaj(p_el);
int ispis(p_el);
int trazi(p_el, int);

int main()
{
	_el head;
	head.next = NULL;
	head.prev = NULL;

	dodaj(&head);
	dodaj(&head);
	dodaj(&head);
	ispis(head.next);
	trazi(&head, 2);

	return 0;
}

int dodaj(p_el p)
{
	p_el temp;
	p_el novi = (p_el)malloc(sizeof(struct el));
	
	if (novi == NULL)
		return -1;

	puts("Unesi vrijednost novog elementa!");
	scanf("%d", &novi->broj);

	if (p->next != NULL) {	//ako lista nije prazna
		temp = p->next;
		temp->prev = novi;
	}
	
	novi->prev = p;
	novi->next = p->next;
	p->next = novi;

	return 0;
}

int trazi(p_el p, int x)
{
	p_el prethodni, sljedeci,temp, head;

	head = p;

	while (p->next != NULL && p->broj != x) {
		temp = p;
		p = p->next;
	}

	if (p->broj == x) {
		puts("trazeni clan je pronaden");

		prethodni = temp;
		sljedeci = p->next;

		if (prethodni != head)
			printf("Prethodi mu %d, ", prethodni->broj);
		else
			printf("Clan nema prethodnika, ");

		if (sljedeci != NULL)
			printf("slijedi ga %d, ", sljedeci->broj);
		else
			printf("nema sljedbenika\n");

	}
	else
		puts("Broj nije pronaden!");
	return 0;
}

int ispis(p_el p)
{
	puts("ISPIS LISTE:");

	while (p != NULL)
	{
		printf("%d  ", p->broj);

		p = p->next;
	}

	return 0;
}