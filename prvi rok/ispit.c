#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct kafic;
struct osoba;

typedef struct kafic* p_kafic;
typedef struct osoba* p_osoba;

typedef struct kafic{
    char ime[256];
    p_kafic next;
    p_osoba head;
        
}_kafic;

typedef struct osoba{
    char ime[256];
    char prezime[256];
    p_osoba next;
        
}_osoba;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
int readFromBuffer(char*, p_kafic);
p_kafic createKafic(char*);
int pushKafic(p_kafic, p_kafic);
int ponavljanje(p_kafic, char*);
int sortiraniUnosKafic(p_kafic, p_kafic);
int sortiraniUnosOsoba(p_osoba, p_osoba);
void ispisKafica(p_kafic);
p_osoba createOsoba(char*, char*);
void insertOsoba(p_osoba,char*, p_kafic);
void ispisOsoba(p_osoba p);
void podatci(p_kafic, char*);
void freeMemory(p_kafic);
void deleteList(p_osoba);

int main()
{

    FILE* fp = NULL;

    int buffer_size = 0;
    char* buffer;
    char trazeni[256];

    _kafic HEAD_kafici;
    HEAD_kafici.next = NULL;

    fp = fopen("kafici.txt", "r");
    if(fp == NULL){
        puts("Datoteka nije otvorena!");
        return -1;      
    }else puts("Datoteka je otvorena!");

    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);
    fclose(fp);

    readFromBuffer(buffer, &HEAD_kafici);
    puts("Ispis kafica!");
    ispisKafica(&HEAD_kafici);

    puts("Upisi ime kafica cije podatke zelis vidjeti!");
    scanf("%s", trazeni);
    podatci(&HEAD_kafici, trazeni);

    freeMemory(&HEAD_kafici);
    return 0;
}

void freeMemory(p_kafic p)
{
    p = p->next;
    p_kafic temp = p->next;

    while(p != NULL){
        deleteList(p->head);

        temp = p;
        p = p->next;
        printf("Izbrisan kafic %s\n", temp->ime);
        free(temp);
    }
}

void deleteList(p_osoba p)
{
    p = p->next;
    p_osoba temp = p;

    while(p!=NULL){
        
        
        temp = p;
        p = p->next;

        printf("Brisem %s\n", temp->ime);
        free(temp);
    }

    
}

void podatci(p_kafic p, char* trazeni)
{
    int count = 0;
    p_osoba i;
    p = p->next;
    while( p != NULL && strcmp(p->ime, trazeni))
        p = p->next;

    if( p == NULL){
        puts("Nije pronaden!");
        return;
    }

    else{
        printf("Pronaden %s\n", p->ime);
    }

    i = p->head->next;
    while(i != NULL){
        count++;
        i = i->next;
    }
    printf("Broj ljudi u kaficu je %d\n", count);
    puts("To su:");
    ispisOsoba(p->head);
}

int readFromBuffer(char* buffer, p_kafic HEAD_kafici)
{
    int n = 0;
    int r = 0;
    char ime_kafic[256];
    char ime_osoba[256];
    char prezime_osoba[256];

    while( r != -1){
        r = sscanf(buffer, "%s %s %s%n", ime_osoba, prezime_osoba, ime_kafic, &n);

        if( r == -1){
            puts("Kraj datoteke/greska!");
            break;
        }

        if( r == 3){
            //printf("Ucitan kafic %s\n", ime_kafic);
            pushKafic(createKafic(ime_kafic), HEAD_kafici);
            insertOsoba( createOsoba(ime_osoba, prezime_osoba) ,ime_kafic , HEAD_kafici);
        }

        buffer += n;

    }
    return 0;
}

void insertOsoba(p_osoba new_el, char* kafic, p_kafic p)
{ 
        while( p->next != NULL && strcmp(kafic, p->next->ime) != 0){
            p = p->next;
        }

        if( p->next != NULL){
            //printf("Pronaden kafic %s\n", p->next->ime);
            sortiraniUnosOsoba(p->next->head, new_el);
            printf("%s :", p->next->ime);
            //ispisOsoba(p->next->head);
        }
}

p_osoba createOsoba(char* ime, char* prezime)
{
    p_osoba new_el = (p_osoba)malloc(sizeof(_osoba));

    new_el->next = NULL;
    strcpy(new_el->ime, ime);
    strcpy(new_el->prezime, prezime);
    //printf("Napravljena osoba %s\n", new_el->ime);
    return new_el;
}


int pushKafic(p_kafic new_el, p_kafic p)
{
    if( p->next == NULL){   //ako je lista prazna
        new_el->next = p->next;
        p->next = new_el;

        //printf("Dodan element %s\n", new_el->ime);
        return 0;
    }

    else{
        if(ponavljanje(p, new_el->ime)){
            sortiraniUnosKafic(p, new_el);
           // printf("Dodan element %s\n", new_el->ime);
        }

        else{
            free(new_el);
        }
    }

    return 0;
}

int sortiraniUnosOsoba(p_osoba p, p_osoba new_el)
{

    if( p->next == NULL){   //ako je lista prazna
        new_el->next = p->next;
        p->next = new_el;

        //printf("Dodan element %s\n", new_el->ime);
        return 0;
    }  
    else{
        while(p->next != NULL  && strcmp(p->next->ime, new_el->ime) < 0)
            p = p->next;

        new_el->next = p->next;
        p->next = new_el;

    }
}

int sortiraniUnosKafic(p_kafic p, p_kafic new_el) // p == head
{
    while(p->next != NULL  && strcmp(p->next->ime, new_el->ime) < 0)
        p = p->next;

    new_el->next = p->next;
    p->next = new_el;

    return 0;
}

void ispisKafica(p_kafic p){
    p = p->next;

    while(p != NULL){
        printf("%s ", p->ime);
        p = p->next;
    }

    puts("");
}

void ispisOsoba(p_osoba p){
    p = p->next;

    while(p != NULL){
        printf("%s ", p->ime);
        p = p->next;
    }

    puts("");
}

int ponavljanje(p_kafic p, char* trazeni)   //p = head
{
    p = p->next;

    while( p != NULL && strcmp(p->ime, trazeni) != 0){
        p = p->next;
    }

    if( p == NULL){
        //puts("Nema podudaranja!");
        return 1;
    }

    else{
        //puts("Kafic postoji!");
        return 0;
    }
}

p_kafic createKafic(char* ime)
{
    p_kafic new_el = (p_kafic)malloc(sizeof(_kafic));
    new_el->next = NULL;
    new_el->head = (p_osoba)malloc(sizeof(_osoba));
    new_el->head->next = NULL;
    strcpy(new_el->ime, ime);
    //printf("Stvoren kafic %s\n", new_el->ime);

    return new_el;
}

char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(sizeof(char), buffer_size + 10);

    fread(buffer, 1, buffer_size, fp);

    //printf("Sadrzaj datoteke je %s\n", buffer);
    return buffer;
    
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;

    fseek(fp, 0, SEEK_END);
    buffer_size = ftell(fp);
    rewind(fp);

    //printf("Velicina buffer je %d\n", buffer_size);
    return buffer_size;
}
