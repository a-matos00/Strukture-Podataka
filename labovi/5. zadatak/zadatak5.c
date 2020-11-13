#include<stdio.h>
#include<stdlib.h>

typedef struct el* p_el;

typedef struct el{
	int broj;
	p_el next;	
}_el;

int sortiraniUnos(p_el);
int ispis(p_el);

int main()
{
	_el L1, L2;

	L1.next = NULL;
	L2.next = NULL;

	sortiraniUnos(L1.next);
	
	return 0;
}

int sortiraniUnos(p_el p)	//argument je head element
{
	p_el novi;
	int i;

	puts("Unijeti ce se 5 brojeva u skup");

	for( i = 0; i < 5; i++)
	{

		novi = (p_el)malloc(sizeof(_el));

		printf("Unesi broj: ");	//unos podataka
		scanf("%d", novi->broj);

		if( p->next == NULL)	//prvi unos
		{
			novi->next = p->next;	//dodajemo prvi clan u listu
			p->next = novi;

			p = novi;
		}

		else{	//ako vec postoje neki elementi u nizu
			if( p->broj > novi->broj)
			{

			}
		}

		p = p->next;
	}

	return 0;
}
