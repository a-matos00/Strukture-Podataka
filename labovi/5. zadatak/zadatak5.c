#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Header.h"	//struktura, pomocne funkcije

#define N 5	//velicina listi

int ispuniListuRand(p_el);
int generirajRand();
p_el alocNoviEl();
int unosPrvogEl(p_el, p_el);
int ispis(p_el);
int sortiraniUnos(p_el, p_el);
int presjek(p_el, p_el, p_el);
int unija(p_el, p_el, p_el);
int UnosKraj(p_el, p_el);

int main()
{
	_el L1, L2, rezP, rezU;
	char c;

	L1.next = NULL;
	L2.next = NULL;
	rezP.next = NULL;
	rezU.next = NULL;


	ispuniListuRand(&L1);

	do {
		puts("Pricekaj sekundu pa stisni enter za generiranje listi");	//jako bitno jer bez ovoga se generira isti seed za obe liste pa budu iste

		scanf("%c", &c);

	} while (c != '\n');
	
	ispuniListuRand(&L2);
	
	printf("Ispis prve liste:  ");
	ispis(&L1);
	puts("");
	printf("Ispis druge liste:  ");
	ispis(&L2);
	puts("");

	presjek(&L1, &L2, &rezP);
	printf("Presjek listi je: ");
	ispis(&rezP);

	puts("");
	unija(&L1, &L2, &rezU);
	printf("Unija listi je: ");
	ispis(&rezU);


	return 0;
}

int unija(p_el p1, p_el p2, p_el rezU)
{
	p_el temp = rezU;

	p1 = p1->next;
	p2 = p2->next;

	while(p1 != NULL && p2 != NULL)
	{
		p_el novi = (p_el)malloc(sizeof(_el));

		if (p1->broj < p2->broj)
		{
			novi->broj = p1->broj;

			unosKraj(rezU, novi);

			p1 = p1->next;
		}

		else if (p1->broj > p2->broj)
		{
			novi->broj = p2->broj;

			unosKraj(rezU, novi);

			p2 = p2->next;
		}

		else if (p1->broj == p2->broj)
		{
			novi->broj = p1->broj;
			unosKraj(rezU, novi);

			p1 = p1->next;
			p2 = p2->next;
		}
	}

	if (p1 == NULL)
	{
		
		while (p2 != NULL) {
			p_el novi = (p_el)malloc(sizeof(_el));
			novi->broj = p2->broj;
			unosKraj(rezU, novi);

			p2 = p2->next;
		}
	}

	if (p2 == NULL)
	{

		while (p1 != NULL) {
			p_el novi = (p_el)malloc(sizeof(_el));
			novi->broj = p1->broj;
			unosKraj(rezU, novi);

			p1 = p1->next;
		}
	}
	return 0;
}

int presjek(p_el p1, p_el p2, p_el rezP)
{
	p_el p2_head = p2;
	p_el novi;

	p1 = p1->next;
	p2 = p2->next;

	while (p1 != NULL) {

		while (p2 != NULL) {
			if (p2->broj == p1->broj)
			{
				novi = (p_el)malloc(sizeof(int));
				novi->broj = p2->broj;
				sortiraniUnos(rezP, novi);

				p2 = p2_head;

				break;
			}

			else
				p2 = p2->next;
		}

		p1 = p1->next;
		p2 = p2_head;
	}
	return 0;
}

int ispuniListuRand(p_el p)	//ispunjava listu velicine N nasumicnim brojevima
{
	int i = 0;
	int j = 0;
	int randBroj;

	int* niz = (int*)malloc(sizeof(int));	//sluzi za provjeru duplikata
	int vel_niza = 1;
	
	p_el head = p;

	srand(time(NULL));

	for (i = 0; i < N; i++) {	//lista ce sadrzavati N clanova

		p_el novi = alocNoviEl();	//alocira se prostor za novi element liste

		randBroj = generirajRand();	//generiran je nasumicni broj

		if (vel_niza == 1)
		{
			niz[0] = randBroj;
			vel_niza += 1;

		}
		
		else
		{
			for (j = 0; j < vel_niza; j++)
			{
				if (niz[j] == randBroj)
				{
					randBroj = generirajRand();
					j = -1;
				}
			}

			vel_niza += 1;
			niz = (int*)realloc(niz, vel_niza * sizeof(int));

			niz[i] = randBroj;

		}

		novi->broj = randBroj;
		sortiraniUnos(head, novi);	
	}

	
	return 0;
}

