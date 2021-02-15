/*
Napisati program koji:
a) Iz datoteke „drzave.txt“ čita popis država i njihov ID od pročitanih država izgraditi vezanu listu
država na sortirani način od početka prema kraju abecede (treba raditi sortirani unos, a ne
naknadno sortirati). Uz pokazivač na sljedeću državu struktura od koje se gradi vezana lista
mora sadržavati i pokazivač na stablo gradova koji su u toj državi (trenutno NULL) - za 2
b) Iz datoteke „gradovi.txt“ pročitati ime grada i ID države u kojoj se nalazi. Pronaći odgovarajuću
državu u gornjoj listi, te dodati pročitani grad u stablo gradova te države. Za zadanu državu
ispisati sve njene gradove po abecedi. – za 5
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct el;
struct node;

typedef struct el* p_el;
typedef struct node* p_node;

typedef struct node{
    char grad[1024];
    p_node L;
    p_node R;
    
}_node;

typedef struct el{
    char drzava[1024];
    int id;
    p_el next;
    p_node root;
    
}_el;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
void readFromBuffer(char*, p_el);
void sortiraniUnos(p_el, char*, int);
void ispisListe(p_el);

int main()
{
    FILE* fp_drz = NULL;
    FILE* fp_grad = NULL;

    _el head;
    head.next = NULL;
    head.root = NULL;
    
    int buffer_size = 0;
    char* buffer;

    fp_drz = fopen("drzave.txt", "r");

    if(fp_drz == NULL){
        puts("Datoteka nije otvorena!");
        return -1;    
    }
    else
        puts("Datoteka je otvorena!");

    buffer_size = bufferSize(fp_drz);
    buffer = createBuffer(fp_drz, buffer_size);
    fclose(fp_drz);
    
    readFromBuffer(buffer, &head);
    free(buffer);
    ispisListe(&head);

    fp_grad = fopen("gradovi.txt", "r")

    return 0;
}

void ispisListe(p_el p)
{
    p = p->next;
    
    while(p != NULL){
        printf("%s %d ", p->drzava, p->id);
        p = p->next;
    }
    
    return;
}

void sortiraniUnos(p_el p, char* str, int id)
{
    p_el new_node = (p_el)malloc(sizeof(_el));
    new_node->root = NULL;
    new_node->next = NULL;
    new_node->id = id;
    strcpy(new_node->drzava, str);
   // printf("Stvoren element %s %d\n", new_node->drzava, new_node->id);

    
    if(p->next == NULL){
        new_node->next = p->next;
        p->next = new_node;
    }

    else{
        while(p->next != NULL && strcmp(p->next->drzava, str) < 0)
            p = p->next;

        new_node->next = p->next;
        p->next = new_node;
    }

    return;
}

void readFromBuffer(char* buffer, p_el head)
{
    int r = 0;
    int n = 0;
    int id = 0;
    char drzava[1024];

    while( r != -1)
    {
        r = sscanf(buffer, "%s %d%n", drzava, &id, &n);
        
        if(r == -1){
            puts("Greska/kraj datoteke!");
            break;
        }
        
        if(r == 2){
            printf("Ucitana drzava %s sa id %d\n", drzava, id);
            sortiraniUnos(head, drzava, id);
        }
    
        buffer += n;
    }
}



char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = NULL;

    buffer = (char*)malloc(sizeof(char) * buffer_size + 10);

    fread(buffer,1,buffer_size,fp);

    printf("Sadrzaj datoteke je: %s\n", buffer);

    return buffer;
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;
    
    fseek(fp, 0, SEEK_END);

    buffer_size = ftell(fp);

    rewind(fp);

    printf("Velicina buffera je %d\n", buffer_size);
    return buffer_size;
}
