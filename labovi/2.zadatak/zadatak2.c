// strcmp(char[],char[]) --> funkcija usporeduje svaki znak u stringovima te vraca "0" ako su identicni
//ako nisu vratit ce vrijednost koja nije nula

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* p_osoba; //pokazivac na strukturu

typedef struct osoba {
    char ime[20];
    char prezime[20];
    int godina;
    p_osoba next;
}_osoba;

int ispis(p_osoba); //funkcija ispisuje clanove liste
int unosPocetak(p_osoba); //funkcija dodaje novi clan na pocetak liste
int unosKraj(p_osoba);    //funkcija unosi novi clan na kraj liste
int traziPrezime(p_osoba);    //funkcija trazi clan u listi po prezimenu
int traziUkloni(p_osoba); //funkcija trazi clan po prezimenu te ga uklanja iz liste

int main()
{
    _osoba head;  //inicijalizacija pocetnog clana liste
    head.next = NULL; //postavljamo da prvi clan pokazuje na nista jer je trenutno jedini clan u listi

    unosPocetak(&head);
    unosPocetak(&head);
    ispis(head.next);
    unosKraj(&head);
    unosKraj(&head);
    ispis(head.next);
    traziPrezime(head.next);
    traziUkloni(head.next);
    ispis(head.next);


    return 0;
}

int unosPocetak(p_osoba p) //u funkciju smo poslali adresu HEAD clana
{
    p_osoba q = (p_osoba)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    if (q == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    puts("Unesi ime:"); //unos podataka
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    q->next = p->next;  //dodani clan sada pokazuje na ono na sto je prije pokazivao HEAD clan
    p->next = q;  //HEAD clan sada pokazuje na dodani clan

    return 0;
}

int unosKraj(p_osoba p)    //argument je adresa HEAD clana
{
    p_osoba q = (p_osoba)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    if (q == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    puts("Unesi ime:"); //unos podataka
    scanf("%s", q->ime);
    puts("Unesi prezime:");
    scanf("%s", q->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &q->godina);

    while (p->next != NULL) {   //dok ne dodemo do zadnjeg clana u listi
        p = p->next;    //prebacujemo se na sljedeci clan
    }
    p->next = q;  //bivsi zadnji clan sada pokazuje na novi clan
    q->next = NULL;     //novi clan mora pokazivati na nista jer je zadnji u listi

    return 0;
}

int ispis(p_osoba p)   //argument je adresa prvog stvarnog clan liste
{
    puts("Ispis popisa ljudi:\n");

    while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
    {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis podataka trenutnog clana liste
        p = p->next;    //prebacujemo se na sljedeci clan u listi
    }

    return 0;
}

int traziPrezime(p_osoba p) //argument je adresa prvog stvarnog clan liste
{
    char prezime[20];   //u ovu varijablu upisujemo prezime koje trazimo

    puts("Upisi prezime koje trazite:");
    scanf("%s", prezime);   //unosimo trazeno prezime

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //petlja se vrti dok ne dodemo do zadnjeg clana i dok vrijednost varijable prezime ne odgovara trazenom prezimenu(vidi vrh za objasnjenje strcmp();
    {
        p = p->next;    //prebacujemo se na sljedeci clan liste
    }

    if (strcmp(prezime, p->prezime) == 0)   //ako smo pronasli trazeni clan
        printf("p_osoba je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis trazenog clana

    else if (strcmp(prezime, p->prezime) != 0)  //ako trazeni clan nije pronaden
        puts("Trazeno prezime ne postoji u listi"); //prigodna poruka

    return 0;
}

int traziUkloni(p_osoba p) //argument je adresa HEAD clana
{
    char prezime[20];
    p_osoba temp = (p_osoba)malloc(sizeof(_osoba));    //stvaramo privremenu varijablu koja sluzi za oznacavanje clana koji prethodi trazenom clanu

    if (temp == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    puts("Upisi prezime osobe koju zelis ukloniti:");
    scanf("%s", prezime);

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //isti uvjet kao kod traziPrezime()
    {
        temp = p;   //spremamo adresu trenutnog clana jer ce nam poslije sluziti kao adresa clana koji prethodi trazenom clanu
        p = p->next;    //prebacujemo se na sljedeci clan
    }

    if (strcmp(prezime, p->prezime) == 0) { //ako smo pronasli trazeni clan
        temp->next = p->next;   //clan koji prethodi uklonjenom clanu ce sada pokazivati na clan liste koji slijedi nakon uklonjenog
        free(p);    //oslobadamo memoriju izbacenog clana liste
    }

    else if (strcmp(prezime, p->prezime) != 0)
        puts("Trazeno prezime ne postoji u listi");

    return 0;
}