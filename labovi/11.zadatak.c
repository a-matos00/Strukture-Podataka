#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 999
#define MAX_STR_SIZE 100
#define FALSE 0
#define TRUE 1

struct student;

typedef struct student* p_student;

typedef struct student {
    char name[100];
    char surname[100];
    int id;
    p_student next;
}_student;

int hashKeyGen(char*);   //(name, hash table);
int store(char*, char*, int, p_student);
int findId(char*, char*, p_student);
int stringCompare(char*, char*);
p_student createStruct(char*, char*, int);

int main()
{
    p_student hash_table = (p_student)malloc(sizeof(_student) * TABLE_SIZE);
    char action[3];
    char name[MAX_STR_SIZE];
    char surname[MAX_STR_SIZE];
    int id = 0;
    int i = 0;

    for (i = 0; i < TABLE_SIZE; i++) {
        (hash_table + i)->id = NULL;
    }

    puts("PRESS KEY FOR ACTION: 'a' add new student, 'q'- exit program");

    while(strcmp(action, "q") != 0){
        puts("PRESS KEY FOR ACTION:");
        scanf("%s", action);

        if( strcmp(action, "a") == 0 && strlen(action) < 2){
            printf("Enter student name, surname, id: ");
            scanf("%s %s %d", name, surname, &id);
            
            store(name, surname, id, hash_table);
        }
        else if( strcmp(action, "f") == 0 && strlen(action) < 2){
            printf("(FIND)Enter student name: ");
            scanf("%s %s", name, surname);
            findId(name, surname, hash_table);
        }
        
        else
            puts("WRONG INPUT!");
    }

    return 0;
}

int stringCompare(char* str1, char* str2)   //(1 == true, 0 == false)
{
    int i = 0;
    if( strlen(str1) != strlen(str2) ){ //compare size
        return FALSE;
    }
    
    else
        for( i = 0; i < strlen(str1); i++)
            if(str1[i] != str2[i])
                return FALSE;
    return TRUE;
}

int findId(char* name, char* surname, p_student table)
{
    int key = hashKeyGen(surname);
    p_student p = (table + key);
    
    if( (table + key)->id == NULL){
        puts("Key place is empty!");
        return 0;
    }
    
    while (p != NULL)
    {
        if (stringCompare(name, p->name) && stringCompare(surname, p->surname))
        {
            printf("Student ID is %d\n", p->id);
            return p->id;
        }
        printf("Nije pronaden iden dalje!\n");
        p = p->next;
    }

    printf("nema ga!\n");

    return 1;
}

int store(char* name, char* surname, int id, p_student table)
{
    int hash_key = hashKeyGen(surname);
    p_student new_student = table + hash_key;

    if ((table + hash_key)->id == NULL) {
        strcpy((table + hash_key)->name, name);
        strcpy((table + hash_key)->surname, surname);
        (table + hash_key)->id = id;
        (table + hash_key)->next = NULL;
        printf("Stored value %s %s %d to the hash table with key %d\n", (table + hash_key)->name, (table + hash_key)->surname, (table + hash_key)->id, hash_key);
    }
    else {
        while (new_student->next != NULL)
            new_student = new_student->next;

            new_student->next = createStruct(name, surname, id);
            printf("Stored value %s %s %d to the hash table with key %d\n", (table + hash_key)->next->name, (table + hash_key)->next->surname, (table + hash_key)->next->id, hash_key);       
    }

    return 0;
}

p_student createStruct(char* name, char* surname, int id){
    p_student new_student = (p_student)malloc(sizeof(struct student));

    strcpy( new_student->name, name);
    strcpy(new_student->surname, surname);
    new_student->id = id;
    new_student->next = NULL;

    return new_student;
}

int hashKeyGen(char* str)
{
    int key = 0;
    int i;
    
    if( strlen(str) == 0 ){
        puts("ERROR! (Empty string, cannot generate hash key)");
        return -1;
    }
    
    for( i = 0; i < strlen(str); i++)   //sum of ascii codes of each character of string
        key += *(str + i);

    key %= TABLE_SIZE;

   // printf("Hash key for value %s is %d\n", str, key);
    
    return key;
}
