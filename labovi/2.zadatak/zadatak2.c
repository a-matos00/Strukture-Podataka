#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* element; 

typedef struct osoba {
    char ime[20];
    char prezime[20];
    int godina;
    element* next; 
}_osoba;


void ispis(element*); 
void unos(element*);
void unosKraj(element*);
void traziPrezime(element*);
void traziUkloni(element*);

int main()
{
    _osoba head;  
    head.next = NULL; 

    unosKraj(&head);
    unosKraj(&head);
    traziPrezime(head.next);
    ispis(head.next);

    return 0;
}

void unos(element p)
{
    element q;

    q = (element)malloc(sizeof(_osoba)); 

    puts("Unesi ime:");
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    q->next = p->next;  
    p->next = q;  
}

void unosKraj(element p)
{
    element q; 

    q = (element)malloc(sizeof(_osoba)); 

    puts("Unesi ime:");
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    while (p->next != NULL) {
        p = p->next;
    }
        p->next = q;  
        q->next = NULL;     
}

void ispis(element p)
{
    puts("Ispis popisa ljudi:\n");
    while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
    {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);  //ispisujemo vrijednost varijable "godina" trenutne strukture
        p = p->next;    //  svaki clan liste sadrzi adresu sljedeceg clana te ce sada vrijednost varijable "p" biti upravo ta adresa sljedeceg clana
    }
}

void traziPrezime(element p)
{
    char prezime[20];

    puts("Upisi prezime koje trazite:");
    scanf("%s", prezime);

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0)
    {
        p = p->next;
    }

    if (strcmp(prezime, p->prezime) == 0)
        printf("Element je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina);
    else if (strcmp(prezime, p->prezime) != 0)
        puts("Trazeno prezime ne postoji u listi");
}