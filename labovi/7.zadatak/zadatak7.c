#include<stdio.h>
#include<stdlib.h>

#include "stog.h"
#include "buffer.h"



int bufferSize(FILE* fp);
char* createBuffer(FILE*);
int izrRezPostfix(p_el, char*);
p_el newElement(int);
int push(p_el, p_el);
int ispis(p_el);
int* operandi(p_el);
int operacija(p_el, char);
int pop();


int main()
{
	FILE* fp;
	_el HEAD_stog;
	HEAD_stog.next = NULL;
	int rezultat = 0;

	char* postfix_izraz;

	fp = fopen("postfix.txt", "r");

	if( fp == NULL){
		puts("Greska u otvaranju datoteke");
		return -1;
	}

	postfix_izraz = createBuffer(fp);
	
	rezultat = izrRezPostfix(&HEAD_stog, postfix_izraz);

	printf("Rezultat postfix izraza je %d", rezultat);
	system("pause");

	return 0;
}

int* operandi(p_el p) {

	int* operandi = 0;

	if (p == NULL) {
		puts("NEISPRAVAN ARGUMENT(null pointer)!");
		return NULL;
	}

	else if (p->next == NULL || p->next->next == NULL) {
		puts("Nedovoljan broj argumenata!");
		return NULL;
	}
	
	operandi = (int*)malloc(sizeof(int) * 2);

	*(operandi + 0) = p->next->broj;
	*(operandi + 1) = p->next->next->broj;

	
	return operandi;

}

int operacija(int* operandi, char operator)
{
	int a = 0, b = 0;

	b = *(operandi + 0);
	a = *(operandi + 1);

	if (operandi == NULL) {
		puts("Greska pri pronalazenju operanada");
		return -1;	//UPITNO!!!!
	}

	switch (operator) {

	case '+': return a + b; break;
	case '*': return a * b; break;

	}
}

int izrRezPostfix(p_el HEAD_stog, char* str)
{
	int r;
	int read_offset = 0;
	char operator;
	int znak;
	int rezultat = 0;

	while (str != EOF) {

		r = sscanf(str, "%d%n", &znak, &read_offset);

		/* printf("READ OFFSET == %d\n", read_offset);
		printf("RETURN VALUE === %d\n", r);
		printf("%s\n", str);
		*/	//ZA DEBUG

		if (r == EOF) {
			//puts("Kraj datoteke");	//debug
			return -1;
		}

		if (r == 1) {
			printf("Ucitan je broj %d\n", znak);
		
			push(HEAD_stog, newElement(znak));
			
			ispisStoga(HEAD_stog);
		}

		if (r == 0) {
			operator = *(str + 1);
			printf("Ucitan je znak %c\n", operator);

			rezultat = operacija(operandi(HEAD_stog), operator);

		}

		str += read_offset;	//pomice se pokazivac u stringu
	}

	return rezultat;
}







