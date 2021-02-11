/*
Strukture podataka – 2 ispitni rok
27.2.2014.
Napisati program koji iz datoteke čita dio teksta, riječ po riječ i unosi u binarno stablo pretraživanja
(maksimalna duljina riječi 1024 znaka). Ispisati binarno stablo na „inorder“ način.
Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve riječi koje počinju samoglasnikom, a u
drugoj sve riječi koje počinju suglasnikom. Riječi zapisane u datotekama moraju biti sortirane po abecedi.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;
struct el;

typedef struct node* p_node;
typedef struct el* p_el;

typedef struct node{
    char word[1024];
    p_node L;
    p_node R;
    
}_node;

typedef struct el{
    char word[1024];
    p_el next;
    
}_el;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
p_node createNode(char*);
p_node addNode(p_node, p_node);
p_node readWords(p_node, char*);
void printInOrder(p_node);
p_el findSamo(p_node, p_el);
p_el findSugl(p_node, p_el);
void addToList(p_el, char*);
void ispisLista(p_el);
void writeToFile(FILE*, p_el);

int main()
{
    int buffer_size = 0;
    char* buffer;
    p_node root = NULL;
    p_el headSa = (p_el)malloc(sizeof(_el)); 
    headSa->next = NULL; 

    p_el headSu = (p_el)malloc(sizeof(_el)); 
    headSu->next = NULL; 
    

    FILE* fp = NULL;
    FILE* fp_samo = NULL;
    FILE* fp_sugl = NULL;

    fp = fopen("dat.txt","r");

    if(fp == NULL)
    {
        puts("Datoteka nije otvorena!");
        return -1;
    }
    else
        puts("Datoteka otvorena!");

    buffer_size = bufferSize(fp);
    printf("Velicina buffera je %d\n", buffer_size);

    buffer = createBuffer(fp, buffer_size);

    printf("Sadrzaj datoteke je: %s\n", buffer);

    root = readWords(root, buffer);

    printInOrder(root);
    puts("");

    headSa = findSamo(root, headSa);
    headSu = findSugl(root, headSu);

    ispisLista(headSa);
    ispisLista(headSu);

    fp_samo = fopen("samoglasnici", "w");
    fp_sugl = fopen("suglasnici", "w");
    
    writeToFile(fp_samo, headSa);
    writeToFile(fp_sugl, headSu);

    fclose(fp);
    fclose(fp_samo);
    fclose(fp_sugl);
    free(root);
    free(headSa);

    return 0;
}

void writeToFile(FILE* fp, p_el p)
{
    p = p->next;

    while(p != NULL){
        fwrite(p->word, sizeof(char), strlen(p->word), fp);
        fwrite(" ", sizeof(char), 1, fp);
        p = p->next;
    }
        
}

void ispisLista(p_el p)
{
    p = p->next;
    
    while(p != NULL){
        printf("%s ", p->word);
        p = p->next;
    
    }
    puts("");
    return;
}

void addToList(p_el p, char* str)
{
    p_el new_node = (p_el)malloc(sizeof(_el));
    strcpy(new_node->word, str);

    
    if(p->next == NULL) //ako je lista prazna
    {
        new_node->next = p->next;
        p->next = new_node;
        return;
    }

    else{
        while( p->next != NULL && strcmp(p->next->word, new_node->word) < 0 )
            p = p->next;

        new_node->next = p->next;
        p->next = new_node;

        return;
    }
        
    
}

p_el findSamo(p_node current, p_el list)
{
    if(current == NULL)
        return list;
    
    findSamo(current->L, list);
    
    findSamo(current->R, list);

        if( current->word[0] == 'a' || current->word[0] == 'e' || current->word[0] == 'i' || current->word[0] == 'o' || current->word[0] == 'u')
        addToList(list, current->word);

    return list;
}

p_el findSugl(p_node current, p_el list)
{
    if(current == NULL)
        return list;
    
    findSugl(current->L, list);
    
    findSugl(current->R, list);

        if( current->word[0] != 'a' && current->word[0] != 'e' && current->word[0] != 'i' && current->word[0] != 'o' && current->word[0] != 'u')
        addToList(list, current->word);

    return list;
}

void printInOrder(p_node current)
{
    if(current == NULL)
        return;

    printInOrder(current->L);
    printf("%s ", current->word);
    printInOrder(current->R);
}
p_node readWords(p_node root, char* buffer)
{
    int r = 0;
    int n = 0;
    char word[1024];
    p_node new_node;

    while(r != -1)
    {
        r = sscanf(buffer, "%s%n", word, &n);

        if( r == -1){
            puts("Greska/kraj datoteke!");
            break;        
        }

        if( r == 1){
            printf("Ucitana rijec: %s\n", word);
            new_node = createNode(word);
            root = addNode(root, new_node);
        }

        buffer += n;
    }

    return root;
}

p_node addNode(p_node current, p_node new_node)
{
    if(current == NULL)
        return new_node;

    if( strcmp(current->word, new_node->word) > 0){
        printf("Idem lijevo\n");
        current->L = addNode(current->L, new_node);
    }
    
    else if( strcmp(current->word, new_node->word) < 0){
        printf("Idem desno\n");
        current->R = addNode(current->R, new_node);
    }
    
    return current;
}

p_node createNode(char* str)
{
    p_node new_node = (p_node)malloc(sizeof(_node));

    strcpy(new_node->word, str);
    new_node->L = NULL;
    new_node->R = NULL;
    printf("Stvoren cvor %s\n", new_node->word);
    
    return new_node;
}

char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(buffer_size, sizeof(char));

    fread(buffer,1,buffer_size,fp);

    rewind(fp);

    return buffer;
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;

    fseek(fp,0, SEEK_END);
    buffer_size = ftell(fp);

    rewind(fp);

    return buffer_size + 10;
}





