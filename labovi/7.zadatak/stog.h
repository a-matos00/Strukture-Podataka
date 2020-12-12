#pragma once

typedef struct el* p_el;

typedef struct el {
	int broj;
	p_el next;
}_el;

int ispisStoga(p_el p)
{

	if (p == NULL) {
		puts("Neispravan argument!");
		return -1;
	}

	p = p->next;

	printf("Ispis stoga: ");

	while (p != NULL)
	{
		printf("%d ", p->broj);
		p = p->next;
	}
	puts("");

	return 0;
}