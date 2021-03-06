//cirkularna lista

#include<stdio.h>

typedef struct clan* p_clan;

typedef struct clan {
	int broj;
	p_clan next;
}_clan;

int unosPocetak(int, p_clan);
int unosKraj(int, p_clan);
int ispis(p_clan);

int main()
{
	_clan head;
	head.next = &head;

	unosKraj(5, &head);
	unosKraj(3, &head);
	unosKraj(7, &head);
	ispis(&head);

	return 0;
}

int ispis(p_clan p)	//arg je head element
{
	p_clan head = p;	

	if (p->next == head) {	//ako je lista prazna
		puts("Prazna lista");
		return -1;
	}
	
	p = p->next;
	while (p != head) {

		printf("%d", p->broj);

		p = p->next;
	}

	return 0;
}

unosKraj(int br, p_clan p)
{
	p_clan head = p;

	p_clan novi = (p_clan)malloc(sizeof(_clan));

	novi->broj = br;

	while (p->next != head)
	{
		p = p->next;
	}

	novi->next = head;
	p->next = novi;


}

int unosPocetak(int br, p_clan p)
{
	p_clan novi = (p_clan)malloc(sizeof(_clan));

	novi->broj = br;

	novi->next = p->next;
	p->next = novi;

	return 0;
}
