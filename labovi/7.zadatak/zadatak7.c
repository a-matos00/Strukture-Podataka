#include<stdio.h>
#include<stdlib.h>

typedef struct el* p_el;

typedef struct el{
	int broj;
	p_el next;
}_el;

int bufferSize(FILE* fp);
char* createBuffer(FILE*);
int izrRezPostfix(p_el, char*);
p_el newElement(int);

int main()
{
	FILE* fp;
	_el HEAD_stog;

	char* postfix_izraz;

	fp = fopen("datoteka.txt", "r");

	if( fp == NULL){
		puts("Greska u otvaranju datoteke");
		return -1;
	}

	postfix_izraz = createBuffer(fp);
	
	izrRezPostfix(&HEAD_stog, postfix_izraz);

	system("pause");

	return 0;
}

int izrRezPostfix(p_el p, char* str)
{
	int ss_return_val;
	int n;

	ss_return_val = sscanf(str, "%d", , &n);

	return 0;
}

p_el newElement(int arg_br)
{
	p_el novi_el = (p_el)malloc(sizeof(_el));
	novi_el->broj = arg_br;

	return novi_el;
}

int push(p_el p, p_el novi)	//argument je head element
{

	if( p == NULL){
		puts("Neispravan argument, null pokazivac");
		return -1;
	}

	novi->next = p->next;
	p->next = novi;

	return 0;
}

char* createBuffer(FILE* fp)
{
	char* buffer;

	buffer = (char*)calloc(bufferSize(fp) + 1, sizeof(char));	//ALOKACIJA BUFFERA
	fread(buffer, bufferSize(fp), 1, fp);	//sadrzaj datoteke se upisuje u buffer

	//printf("Ispis buffera datoteke %s\n", buffer);	za debug

	return buffer;
}

int bufferSize(FILE* fp) {	//racuna se velicina buffera
	int buffer_size = 0;
	
	fseek(fp, 0, SEEK_END);	//stavljam file pointer na kraj
	buffer_size = ftell(fp);	// funkcija vraca kolicinu bajtova od pocetka do trenutne pozicije

	//printf("Velicina buffera je %d znakova\n", buffer_size);	za debuggiranje

	rewind(fp);	//pokazivac datoteke se vraca na pocetak

	return buffer_size;
}
