/*KOMENTARI SU IZ PROSLOG ZADATKA NE CITAJ!!!*/
#include<stdio.h>
#include<stdlib.h>

typedef struct cvor* pozicija;  //deklariramo pokazivac na tip strukture "cvor"

typedef struct cvor {   //deklariramo tip strukture "cvor"
    int broj;
    pozicija* next; //pokazivac na tip strukture "cvor"(sadrzavat ce adresu sljedeceg elementa liste)
};


void ispis(pozicija*);  //funkcija za ispis koja za parametar uzima adresu clana liste
void unos(int, pozicija*);//funkcija prima vrijednost varijable "broj" novog clana liste i adresu prvog clana liste


int main()
{
    struct cvor head;   //inicijaliziramo prvi clan vezane liste
    head.next = NULL;   //posto je on trenutno jedini clan liste pokazuje na "nista", no to ce se uskoro promjeniti odvijanjem programa

    unos(5, &head);
    unos(7, &head);
    unos(69, &head);
    unos(9, &head);
    ispis(head.next);

    return 0;
}

void unos(int x, pozicija p)
{
    pozicija q; //inicijaliziramo novi pokazivac na tip strukture "cvor"

    q = (pozicija)malloc(sizeof(struct cvor));  //rezerviramo prostor u memoriji za novu strukturu tipa "cvor" te pokazivacu "q" dodjeljujemo adresu te strukture 

    while (p->next != NULL) {
        p = p->next;
    }
    q->broj = x;    //varijabli "broj" unutar te strukture dodjeljujemo vrijednost varijable "x"
    p->next = q;
    q->next = NULL;  //varijabli "next" nove strukture dodjeljujemo vrijednost varijable "next" iz clana koji joj prethodi
       
}

void ispis(pozicija p)
{
    while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
    {
        printf("%d  ", p->broj);  //ispisujemo vrijednost varijable "broj" trenutne strukture
        p = p->next;    //  svaki clan liste sadrzi adresu sljedeceg clana te ce sada vrijednost varijable "p" biti upravo ta adresa sljedeceg clana
    }
}
