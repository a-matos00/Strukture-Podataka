#pragma once

typedef struct el* p_el;

typedef struct el {
	float broj;
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
		printf("%.2f ", p->broj);
		p = p->next;
	}
	puts("");

	return 0;
}

int push(p_el head, p_el novi)
{
	if (head == NULL || novi == NULL) {
		puts("Neispravni argumenti!");
		return -1;
	}

	novi->next = head->next;
	head->next = novi;

	return 0;
}

p_el newElement(float arg_br)
{
	p_el novi_el = (p_el)malloc(sizeof(_el));
	novi_el->broj = arg_br;

	return novi_el;
}

int pop(p_el head)
{
	if (head == NULL || head->next == NULL) {
		puts("Greska!(neispravan argument ili prazan stog)");
		return -1;
	}

	p_el temp;

	temp = head->next;

	head->next = temp->next;

	free(temp);

	return 0;
}