//cirkularna lista

#include<stdio.h>

typedef struct clan* p_clan;

typedef struct clan {
	int broj;
	p_clan next;
}_clan;

int unosPocetak(int, p_clan);
int ispis(p_clan);
int izbrisiSKraja(p_clan);

int main()
{
	_clan head;
	head.next = NULL;

	unosPocetak(2, &head);
	unosPocetak(3, &head);
	unosPocetak(5, &head);

	ispis(&head);
	puts("");
	izbrisiSKraja(&head);
	ispis(&head);
	return 0;
}

int izbrisiSKraja(p_clan p)
{
	p_clan prev;

	p_clan head = p;

	while (head->next != NULL) {
		p = head;

		if (head->next == NULL) {
			puts("Izbrisano!");
			break;
		}

		while (p->next != NULL)
		{
			prev = p;
			p = p->next;
		}

		prev->next = NULL;
		free(p);
		
	}


	return 0;
}

int ispis(p_clan p)
{
	if (p->next == NULL) {
		puts("Lista je prazna!");
		return -1;
	}

	p = p->next;
	while (p != NULL) {

		printf("%d ", p->broj);
		p = p->next;
	}
	return 0;
}

int unosPocetak(int br, p_clan p)
{
	p_clan novi = (p_clan)malloc(sizeof(_clan));

	novi->broj = br;

	novi->next = p->next;
	p->next = novi;

	return 0;
}


