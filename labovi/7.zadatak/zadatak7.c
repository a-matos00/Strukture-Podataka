#include<stdio.h>
#include<stdlib.h>

#include "stog.h"
#include "buffer.h"

int bufferSize(FILE* fp);
char* createBuffer(FILE*);
float izrRezPostfix(p_el, char*);
p_el newElement(float);
int push(p_el, p_el);
int ispis(p_el);
float* operandi(p_el);
int operacija(p_el, float*, char);
int pop(p_clan);

int main()
{
	FILE* fp;
	_el HEAD_stog;
	HEAD_stog.next = NULL;
	char* postfix_izraz;

	float rezultat = 0;

	fp = fopen("postfix.txt", "r");

	if( fp == NULL){
		puts("Greska u otvaranju datoteke");
		return -1;
	}

	postfix_izraz = createBuffer(fp);	//sadrzaj datoteke prebacujem u string
	
	rezultat = izrRezPostfix(&HEAD_stog, postfix_izraz);	//funkcija racuna rezultat te ispisuje sve korake

	printf("Rezultat postfix izraza je %.2f\n", rezultat);

	system("pause");

	return 0;
}

float* operandi(p_el p) {	//funkcija stvara niz u kojem se nalaze operandi funkcije

	float *operandi = 0;
	p_el novi = NULL;

	if (p == NULL) {
		puts("NEISPRAVAN ARGUMENT(null pointer)!");
		return NULL;
	}

	else if (p->next == NULL || p->next->next == NULL) {
		puts("Nedovoljan broj argumenata!");
		return NULL;
	}
	
	operandi = (float*)malloc(sizeof(float) * 2);

	*(operandi + 0) = p->next->broj;
	*(operandi + 1) = p->next->next->broj;

	pop(p);	//skida se jedan element sa stoga

	return operandi;

}

int operacija(p_el head, float* operandi, char operator)
{
	float a = 0, b = 0, rez = 0;

	b = *(operandi + 0);
	a = *(operandi + 1);

	if (operandi == NULL) {
		puts("Greska pri pronalazenju operanada");
		return -1;	//UPITNO!!!!
	}

	switch (operator) {	//rezultat operacije se upise u element koji je na vrhu stoga
		case '+':head->next->broj = a + b;
				break;

		case '*':head->next->broj = a * b;
				break;

		case '-': head->next->broj = a + b;
				break;
		case '/': head->next->broj = a / b;
			break;
	}
	
}

float izrRezPostfix(p_el HEAD_stog, char* str)
{
	int r;
	int read_offset = 0;
	char operator;
	float znak = 0;
	float rezultat = 0;

	while (str != EOF) {
		r = sscanf(str, "%f%n", &znak, &read_offset);
		//printf("READ OFFSET == %d\n", read_offset);
		//printf("RETURN VALUE === %d\n", r);
		//printf("%s\n", str);
			//ZA DEBUG

		if (r == EOF) {
			//puts("Kraj datoteke");	//debug
			break;
		}

		if (r == 1) {
			printf("Ucitan je broj %.2f\n", znak);
		
			push(HEAD_stog, newElement(znak));
			
			str += read_offset;
		}

		if (r == 0) {
			operator = *(str + 1);	//+1 radi razmaka
			str += read_offset;

			printf("Ucitan je znak %c\n", operator);

			operacija(HEAD_stog, operandi(HEAD_stog), operator);
			
		}

		ispisStoga(HEAD_stog);
		//pomice se pokazivac u stringu
	}

	rezultat = HEAD_stog->next->broj;

	pop(HEAD_stog);	//uklanja se zadnji clan sa stoga koji sadrzi ukupni rezultat

	return rezultat;
}