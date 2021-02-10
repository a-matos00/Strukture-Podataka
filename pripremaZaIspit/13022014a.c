#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cvor;
struct el;

typedef struct cvor* p_cvor;
typedef struct el* p_el;

typedef struct cvor{
    char* rijec;
    int length;
    p_cvor L;
    p_cvor R;
    
}_cvor;

typedef struct el{
    char* rijec;
    p_el next;
    
}_el;

int bufferSize(FILE*);
char* createBuffer(FILE*, int);
p_cvor createNode(char*);
p_cvor readWords(char*, p_cvor);
p_cvor addNode(p_cvor, p_cvor);
int countChar(p_cvor);
int countWords(p_cvor);
p_el createAverageList(p_cvor, p_el, int);
void addElement(p_el, char*);
void ispisListe(p_el);

int main()
{
    p_cvor root = NULL;
    p_el Head = (p_el)malloc(sizeof(_el));
    Head->next = NULL;

    int total_char;
    int total_words;
    float average;

    char* buffer;
    int buffer_size = 0;
    FILE* fp = NULL;

    fp = fopen("tekst.txt", "r");
    if(fp == NULL){
        puts("Datoteka nije otvorena!");
        return -1;
    }
    else
        puts("Datoteka otvorena!");
 
    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);

    root = readWords(buffer, root);
    
    total_char = countChar(root);
    printf("\nUkupan broj znakova je %d\n", total_char);

    total_words = countWords(root);
    printf("\nUkupan broj rijeci je %d\n", total_words);

    average = (float)total_char / total_words;
    printf("Prosjecna duljina je %f\n", average);

    Head = createAverageList(root, Head, average);

    ispisListe(Head);
    
    return 0;
}

void ispisListe(p_el p)
{
    p = p->next;

    while(p != NULL)
    {
        printf("%s ", p->rijec);
        p = p->next;
    }
}
p_el createAverageList(p_cvor current, p_el list, int average)
{
    if(current == NULL)
        return list;
     
    createAverageList(current->L, list,average);  
    
    if( current->length > average)
        addElement(list, current->rijec);
    
    createAverageList(current->R, list,average);
    
    return list;
}

void addElement(p_el list, char* str)
{
    p_el new_el = (p_el)malloc(sizeof(_el));
    new_el->rijec = str;
    printf("Dodan u vezanu listu: %s\n", new_el->rijec);
    new_el->next = list->next;
    list->next = new_el;
}



p_cvor readWords(char* buffer, p_cvor root)
{
    int n = 0;
    int r = 0;
    char word[100];
    p_cvor new_node;

    while( r != -1){
        r = sscanf(buffer,"%s%n", word, &n);
    
        if( r == -1){
            puts("Greska/kraj datoteke!");
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

int countChar(p_cvor current)
{
    int sum = 0;

    if(current == NULL)
        return sum;
     
    sum += countChar(current->L);  
    sum += current->length;
    sum += countChar(current->R);
    
    return sum;
}

int countWords(p_cvor current)
{
    int word_num  = 0;

    if(current == NULL)
        return word_num;
     
    word_num += countWords(current->L);  
    word_num++;
    word_num += countWords(current->R);
    
    return word_num;
}

p_cvor addNode(p_cvor current, p_cvor new_node)
{
    if(current == NULL)
        return new_node;

    else if( strcmp(new_node->rijec, current->rijec) > 0 ){
        puts("Idem desno");
        current->R = addNode(current->R, new_node);
    }
    if( strcmp(new_node->rijec, current->rijec) < 0 ){
        puts("Idem lijevo");
        current->L = addNode(current->L, new_node);
    }
    return current;
}

p_cvor createNode(char* word)
{
    p_cvor new_node = (p_cvor)malloc(sizeof(_cvor));

    new_node->rijec = (char*)malloc(sizeof(char) * strlen(word));
    strcpy(new_node->rijec, word);
    new_node->length = strlen(word);
    new_node->L = NULL;
    new_node->R = NULL;

    printf("Stvoren cvor %s duljine %d\n", new_node->rijec, new_node->length);
    
    return new_node;
}

char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(buffer_size + 10, sizeof(char));
    
    fread(buffer, buffer_size + 10, 1, fp);
    
    printf("Ucitan je buffer %s\n", buffer);
    
    return buffer;
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;

    fseek(fp, 0, SEEK_END);

    buffer_size = ftell(fp);
    printf("Velicina buffera je %d\n", buffer_size);

    rewind(fp);
    
    return buffer_size;
}
