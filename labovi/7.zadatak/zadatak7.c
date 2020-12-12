#include<stdio.h>
#include<stdlib.h>

#include "stog.h"



int bufferSize(FILE* fp);
char* createBuffer(FILE*);
int izrRezPostfix(p_el, char*);
p_el newElement(int);
int push(p_el, p_el);
int ispis(p_el);
int operacija(char);


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

			//rezultat = operacija(operator);

		}

		str += read_offset;	//pomice se pokazivac u stringu
	}

	return rezultat;
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

p_el newElement(int arg_br)
{
	p_el novi_el = (p_el)malloc(sizeof(_el));
	novi_el->broj = arg_br;

	return novi_el;
}


char* createBuffer(FILE* fp)
{
	char* buffer;

	buffer = (char*)calloc(bufferSize(fp) + 1, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, bufferSize(fp), 1, fp);	//sadrzaj datoteke se upisuje u buffer

	//printf("Ispis buffera datoteke %s\n", buffer);	za debug

	return buffer;
}

int bufferSize(FILE* fp) {	
	int buffer_size = 0;
	
	fseek(fp, 0, SEEK_END);	
	buffer_size = ftell(fp);	

	//printf("Velicina buffera je %d znakova\n", buffer_size);	za debuggiranje

	rewind(fp);	

	return buffer_size;
}
