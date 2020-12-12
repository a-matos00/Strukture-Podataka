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
int operacija(p_el, int*, char);
int pop(p_clan);


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

	postfix_izraz = createBuffer(fp);	//sadrzaj datoteke prebacujem u string
	
	izrRezPostfix(&HEAD_stog, postfix_izraz);	//funkcija racuna rezultat te ispisuje sve korake

	system("pause");

	return 0;
}

int* operandi(p_el p) {	//funkcija stvara niz u kojem se nalaze operandi funkcije

	int* operandi = 0;
	p_el novi;

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

	pop(p);	//skidam jedan element sa stoga

	return operandi;

}

int operacija(p_el head, int* operandi, char operator)
{
	int a = 0, b = 0, rez = 0;

	b = *(operandi + 0);
	a = *(operandi + 1);

	if (operandi == NULL) {
		puts("Greska pri pronalazenju operanada");
		return -1;	//UPITNO!!!!
	}

	switch (operator) {	//rezultat operacije se upise u element koji je na vrhu stoga

	case '+': head->next->broj = a + b; break;
	case '*': head->next->broj = a * b; break;

	}
	return 0;
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

		//printf("READ OFFSET == %d\n", read_offset);
		//printf("RETURN VALUE === %d\n", r);
		printf("%s\n", str);
			//ZA DEBUG

		if (r == EOF) {
			//puts("Kraj datoteke");	//debug
			
			return -1;
		}

		if (r == 1) {
			printf("Ucitan je broj %d\n", znak);
		
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

	return rezultat;
}







