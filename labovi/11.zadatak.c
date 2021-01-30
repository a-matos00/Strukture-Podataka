#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 999
#define MAX_STR_SIZE 100
#define FALSE 0
#define TRUE 1

int hashKeyGen(char*);   //(name, hash table);
int store(char*, char**);
int find(char*, char**);
int stringCompare(char*, char*);

int main()
{
    char** hash_table = (char**)malloc(sizeof(char*) * TABLE_SIZE); //array of pointers to string
    char action[3];
    char temp[MAX_STR_SIZE];

    puts("PRESS KEY FOR ACTION: 'a' add new student, 'q'- exit program");

    while(strcmp(action, "q") != 0){
        puts("PRESS KEY FOR ACTION:");
        scanf("%s", action);

        if( strcmp(action, "a") == 0 && strlen(action) < 2){
            printf("Enter student name: ");
            scanf("%s", temp);
            
            store(temp, hash_table);
        }
        else if( strcmp(action, "f") == 0 && strlen(action) < 2){
            printf("HASH_TABLE[KEY] == %s\n", hash_table[294]);
            printf("(FIND)Enter student name: ");
            scanf("%s", temp);
            printf("HASH_TABLE[KEY] == %s\n", hash_table[294]);
            find(temp, hash_table);
        }
        
        else
            puts("WRONG INPUT!");
    }

    return 0;
}

int stringCompare(char* str1, char* str2)   //(1 == true, 0 == false)
{
    printf("%s and %s\n", str1, str2);
    int i = 0;
    if( strlen(str1) != strlen(str2) ){ //compare size
        puts("Not the same size!");
        return FALSE;
    }
    
    else
        for( i = 0; i < strlen(str1); i++){
            if(str1[i] != str2[i]){
                printf("%c != %c\n", str1[i], str2[i]);
                return FALSE;
            }
            else
                printf("%c == %c\n", str1[i], str2[i]);
        }
    return TRUE;
}

int find(char* str, char** table)
{
    int key = hashKeyGen(str);
    
    printf("%s and %s\n", str,table[key]);
    if(table[key] == NULL){
        puts("Key place is empty!");
        return 0;
    }

    
    else if( stringCompare(str, table[key]) )
        printf("Found item!\n");

    else
        puts("Different size!");

        
    return 0;
}

int store(char* str, char** table)
{
    int str_size = strlen(str) + 1;
    int hash_key = hashKeyGen(str);
    table[hash_key] = (char*)malloc(sizeof(char) * str_size);
    table[hash_key] = str;

    printf("Stored value %s to the hash table with key %d\n", table[hash_key], hash_key);

    return 0;
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

    printf("Hash key for value %s is %d\n", str, key);
    
    return key;
}
