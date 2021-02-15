#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;

typedef struct node* p_node;

typedef struct node{
    char word[1024];
    p_node L;
    p_node R;
    p_node next;
}_node;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
p_node readFromBuffer(char*, p_node);
p_node createNode(char*);
p_node addNode(p_node,p_node);
void ispis(p_node);
void addToList(p_node, p_node);
void ispisLista(p_node);
p_node find(p_node, char*);
int counter(p_node);

int main()
{
    FILE* fp;
    int buffer_size;
    char* buffer;
    fp = fopen("dat.txt", "r");
    int count = 0;

    p_node root = NULL;
    p_node trazeni = NULL;

    if(fp == NULL){
        printf("Datoteka nije otvorena!");
        return -1;
    }
    else{
        printf("Datoteka je otvorena!\n");
    }

    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);
    fclose(fp);

    root = readFromBuffer(buffer, root);
    ispis(root);

    trazeni = find(root, "fesb" );
    counter(trazeni);
    
    return 0;
}

int counter(p_node p)
{
    int count = 0;

    while(p != NULL){
        count++;
        p = p->next;
    }
    printf("rijec se ponavlja %d. puta\n", count);
    return count;
}

p_node readFromBuffer(char* buffer, p_node root)
{
    int r = 0;
    int n = 0;
    char word[1024];
    p_node new_node;

    while( r != -1)
    {
        r = sscanf(buffer, "%s%n", word, &n);
        
        if( r == -1){
            printf("Kraj datoteke/greska!\n");
            break;
        }
       else if( r == 1){
            printf("Ucitana rijec %s\n", word);
            new_node = createNode(word);
            root = addNode(root, new_node);
        }

        buffer += n;
    }
    

    return root;
}

p_node find(p_node current, char* str)
{
    if(current == NULL){
        puts("Rijec nije pronadena!");
        return 0;
    }

   else if( strcmp(current->word, str) > 0){
        puts("Idem lijevo!");
        find(current->L, str);
    }

    else if( strcmp(current->word, str) < 0){
        puts("Idem desno!");
        find(current->R, str);
    }

    else if(strcmp(current->word, str) == 0)
    {
        printf("Cvor pronaden\n");
        return current;
    }

    
}

void ispisLista(p_node p)
{
    while(p != NULL){
        printf("%s ", p->word);
        p = p->next;   
    }
}

void addToList(p_node p, p_node new_node)
{
    new_node->next = p->next;
    p->next = new_node;
}

void ispis(p_node current)
{
    if(current == NULL)
        return;

    ispis(current->L);
    ispisLista(current);
    //printf("%s ", current->word);
    ispis(current->R);

    return;
}

p_node addNode(p_node current, p_node new_node)
{
    if(current == NULL)
        return new_node;

    else if( strcmp(current->word, new_node->word) > 0){
        puts("Idem lijevo!");
        current->L = addNode(current->L, new_node);
    }

    else if( strcmp(current->word, new_node->word) < 0){
        puts("Idem desno!");
        current->R = addNode(current->R, new_node);
    }

    else if(strcmp(current->word, new_node->word) == 0)
    {
        printf("Rijec se ponavlja!\n");
        addToList(current, new_node);
    }

    return current;
}

p_node createNode(char* str)
{
    p_node new_node = (p_node)malloc(sizeof(_node));
    strcpy(new_node->word, str);
    new_node->L = NULL;
    new_node->R = NULL;
    new_node->next = NULL;
    
    printf("Stvoren cvor %s\n", new_node->word);
    return new_node;
}

char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(sizeof(char), buffer_size + 10);

    fread(buffer,1, buffer_size, fp);

    printf("ispis buffera: %s\n", buffer);
           
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
