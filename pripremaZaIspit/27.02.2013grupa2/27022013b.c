#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct el;

typedef struct el* p_el;

typedef struct el{
    char* word;
    p_el next;
}_el;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
void readFromBuffer(char*, p_el);
void sortiraniUnos(p_el, char*);
void ispis(p_el);
void removeFromList(p_el, char*);
void delete(p_el, char*);

int main()
{
    FILE* fp = NULL;
    int buffer_size = 0;
    char* buffer = NULL;

    fp = fopen("readDat.txt", "r");

    _el head;
    head.next = NULL;

    if(fp == NULL){
        puts("Greska kod otvaranja datoteke!");
        return -1;
    }
    else
        puts("Datoteka za citanje otvorena!");

    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);
    fclose(fp);

    readFromBuffer(buffer, &head);
    free(buffer);

    ispis(&head);

    fp = fopen("zaIspis.txt", "r");
    if(fp == NULL){
        puts("Greska kod otvaranja datoteke!");
        return -1;
    }
    else
        puts("Druga datoteka za citanje otvorena!");

    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);
    fclose(fp);

    removeFromList(&head, buffer);

    ispis(&head);
    
    return 0;
}

void removeFromList(p_el head, char* buffer)
{
    int n = 0;
    int r = 0;
    char word[256];

    while( r != -1)
    {
        r = sscanf(buffer, "%s%n", word, &n);

        if( r == -1){
            printf("Greska/kraj datoteke!\n");
            return;
        }
        if( r == 1){
            printf("Ucitana je rijec %s\n", word);
            delete(head, word);
        }

        buffer += n;
    }
}

void delete(p_el p, char* word)
{
    p_el temp;
    temp = p;
    p = p->next;

    while( p != NULL && strcmp(p->word, word) != 0){
        temp = p;
        p = p->next;

    }
    if(p == NULL)
        puts("Rijeci nije pronadena!");

    else{
        temp->next = p->next;
        free(p);
    }
}

void readFromBuffer(char* buffer, p_el head)
{
    int n = 0;
    int r = 0;
    char word[256];

    while( r != -1)
    {
        r = sscanf(buffer, "%s%n", word, &n);

        if( r == -1){
            printf("Greska/kraj datoteke!\n");
            return;
        }
        if( r == 1){
            printf("Ucitana je rijec %s\n", word);
            sortiraniUnos(head, word);
        }

        buffer += n;
    }
}

void ispis(p_el p)
{
    p = p->next;

    if(p == NULL)
    {
        puts("Lista je prazna!");
        return;
    }

    while( p != NULL)
    {
        printf("%s ", p->word);
        p = p->next;
    }

    puts("");
}

void sortiraniUnos(p_el p, char* word)
{
    p_el new_el = (p_el)malloc(sizeof(_el));

    new_el->next = NULL;
    new_el->word = (char*)malloc(sizeof(char) * strlen(word));
    strcpy(new_el->word, word);
    //printf("Stvoren element %s\n", new_el->word);

    if( p->next == NULL){
        new_el->next = p->next;
        p->next = new_el;
    }
    
    else{
        while( p->next != NULL && strcmp(p->next->word, word) > 0)
            p = p->next;

        new_el->next = p->next;
        p->next = new_el;
    }
    return;    
}

char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(sizeof(char), buffer_size + 10);
    
    fread(buffer, 1, buffer_size, fp);
    printf("Sadrzaj datoteke je %s\n", buffer);

    return buffer;
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;
    fseek(fp,0, SEEK_END);
    buffer_size = ftell(fp);
    rewind(fp);
    printf("velicina buffer je: %d\n", buffer_size);

    return buffer_size;
}
