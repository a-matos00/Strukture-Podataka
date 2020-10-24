// strcmp(char[],char[]) --> funkcija usporeduje svaki znak u stringovima te vraca "0" ako su identicni
//ako nisu vratit ce vrijednost koja nije nula

//master
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* element; 

typedef struct osoba {
    char ime[20];
    char prezime[20];
    int godina;
    element next; 
}_osoba;

void ispis(element); //funkcija ispisuje elemente
void unosPocetak(element); //funkcija dodaje novi element na pocetak liste
void unosKraj(element);    //funkcija unosi novi element na kraj liste
void traziPrezime(element);    //funkcija trazi element u listi po prezimenu
void traziUkloni(element); //funkcija trazi element po prezimenu te ga uklanja iz liste

int main()
{
    _osoba head;  //inicijalizacija pocetnog elementa liste
    head.next = NULL; //postavljamo da prvi element pokazuje na nista jer je trenutno jedini element u listi

    unosKraj(&head);
    unosKraj(&head);
    traziPrezime(head.next);
    ispis(head.next);
    traziUkloni(&head);
    ispis(head.next);
   
    return 0;
}

void unosPocetak(element p) //u funkciju smo poslali adresu HEAD elementa
{
    element q = (element)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    puts("Unesi ime:"); //unos podataka
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    q->next = p->next;  //dodani element sada pokazuje na ono na sto je prije pokazivao HEAD element
    p->next = q;  //HEAD element sada pokazuje na dodani element
}

void unosKraj(element p)    //argument je adresa HEAD elementa
{
    element q = (element)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    puts("Unesi ime:"); //unos podataka
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    while (p->next != NULL) {   //dok ne dodemo do zadnjeg elementa u listi
        p = p->next;    //prebacujemo se na sljedeci element
    }
        p->next = q;  //bivsi zadnji element sada pokazuje na novi element
        q->next = NULL;     //novi element mora pokazivati na nista jer je zadnji u listi
}

void ispis(element p)   //argument je adresa prvog stvarnog clan liste
{
    puts("Ispis popisa ljudi:\n");

    while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
    {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis podataka trenutnog elementa liste
        p = p->next;    //prebacujemo se na sljedeci element u listi
    }
}

void traziPrezime(element p) //argument je adresa prvog stvarnog clan liste
{
    char prezime[20];   //u ovu varijablu upisujemo prezime koje trazimo

    puts("Upisi prezime koje trazite:");   
    scanf("%s", prezime);   //unosimo trazeno prezime

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //petlja se vrti dok ne dodemo do zadnjeg clana i dok vrijednost varijable prezime ne odgovara trazenom prezimenu(vidi vrh za objasnjenje strcmp();
    {
        p = p->next;    //prebacujemo se na sljedeci clan liste
    }

    if (strcmp(prezime, p->prezime) == 0)   //ako smo pronasli trazeni clan
        printf("Element je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis trazenog clana

    else if (strcmp(prezime, p->prezime) != 0)  //ako trazeni clan nije pronaden
        puts("Trazeno prezime ne postoji u listi"); //prigodna poruka
}

void traziUkloni(element p) //argument je adresa HEAD elementa
{
    char prezime[20];
    element temp = (element)malloc(sizeof(_osoba));    //stvaramo privremenu varijablu koja sluzi za oznacavanje elementa koji prethodi trazenom clanu

    puts("Upisi prezime osobe koju zelis ukloniti:");
    scanf("%s", prezime);

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //isti uvjet kao kod traziPrezime()
    {
        temp = p;   //spremamo adresu trenutnog elementa jer ce nam poslije sluziti kao adresa elementa koji prethodi trazenom elementu
        p = p->next;    //prebacujemo se na sljedeci element
    }

    if (strcmp(prezime, p->prezime) == 0) { //ako smo pronasli trazeni element
        temp->next = p->next;   //element koji prethodi uklonjenom elementu ce sada pokazivati na element liste koji slijedi nakon uklonjenog
    }

    else if (strcmp(prezime, p->prezime) != 0)
        puts("Trazeno prezime ne postoji u listi");
}
