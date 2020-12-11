#include<stdio.h>
#include<stdlib.h>

typedef struct el* p_el;

typedef struct el
{
	int broj;
	p_el next;
}_el;

int bufferSize(FILE* fp);
char* createBuffer(FILE*);

int main()
{
	FILE* fp;

	char* postfix_izraz;

	fp = fopen("datoteka.txt", "r");

	if( fp == NULL){
		puts("Greska u otvaranju datoteke");
		return -1;
	}

	postfix_izraz = createBuffer(fp);
	
	printf("%s", postfix_izraz); 

	system("pause");

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
