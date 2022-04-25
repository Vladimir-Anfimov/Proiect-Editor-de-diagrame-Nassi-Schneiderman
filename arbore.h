#ifndef ARBORE_H_INCLUDED
#define ARBORE_H_INCLUDED

#include <iostream>
#include <cstring>

using namespace std;

const int CONTENT_SIZE = 100;
const int MAX_CHILDREN = 30;

struct nod {
    char content[CONTENT_SIZE] = "";
    char typeOfBlock[25];
    int nrOfChildren = 0;
    nod *parent = NULL;
    nod* children[MAX_CHILDREN];
    int centruX,lungime;
};

void addNewChild(nod *&nodCurrent, char content[], char typeOfBlock[])
{
    nodCurrent->nrOfChildren++;
    nod *newChild = new nod;
    strcpy(newChild->content, content);
    newChild->parent = nodCurrent;
    strcpy(newChild->typeOfBlock, typeOfBlock);
    nodCurrent->children[nodCurrent->nrOfChildren - 1] = newChild;
}

void goInLastOne(nod *&nodCurrent)
{
    nodCurrent = nodCurrent->children[nodCurrent->nrOfChildren - 1];
}

void goBackToParent(nod *&nodCurrent)
{
    nodCurrent = nodCurrent->parent;
}

void actualizareCoordonateNoduri(nod *nodCurent,int Xcrt)
{
    //lungimea si coordonata x a centrului fiecarui bloc se modifica in functie de tata lui
    if(nodCurent!=NULL)
    {
        if(strcmp(nodCurent->content,""))
        {
            if(strcmp(nodCurent->parent->content,""))
            {
                if(strcmp(nodCurent->parent->typeOfBlock,"IF")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime/2;
                    nodCurent->centruX=nodCurent->parent->centruX-nodCurent->lungime/2;
                }
                else if(strcmp(nodCurent->parent->typeOfBlock,"ELSE")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime;
                    nodCurent->centruX=nodCurent->parent->parent->centruX+nodCurent->lungime/2;
                }
            else if(strcmp(nodCurent->parent->typeOfBlock,"WHILE")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime-nodCurent->parent->lungime/8;
                    nodCurent->centruX=nodCurent->parent->centruX+nodCurent->parent->lungime/16;
                }
            else if(strcmp(nodCurent->parent->typeOfBlock,"FOR")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime-nodCurent->parent->lungime/8;
                    nodCurent->centruX=nodCurent->parent->centruX+nodCurent->parent->lungime/16;
                }
            else if(strcmp(nodCurent->parent->typeOfBlock,"DO_WHILE")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime-nodCurent->parent->lungime/8;
                    nodCurent->centruX=nodCurent->parent->centruX+nodCurent->parent->lungime/16;
                }
            else if(strcmp(nodCurent->parent->typeOfBlock,"CAZ")==0)
                {
                    nodCurent->lungime=nodCurent->parent->lungime;
                    nodCurent->centruX=nodCurent->parent->centruX;
                }
            }
            else
            {
                nodCurent->lungime=DIMENSIUNE.lungime;//cout<<nodCurent->parent->typeOfBlock<<endl;
                nodCurent->centruX=Xcrt;
            }
            if(strcmp(nodCurent->typeOfBlock,"SELECTIE")==0)
                {
                   nodCurent->children[0]->lungime=nodCurent->lungime/nodCurent->nrOfChildren;
                   nodCurent->children[0]->centruX=nodCurent->centruX-nodCurent->lungime/2+nodCurent->children[0]->lungime/2  ;
                   for(int i=1;i<nodCurent->nrOfChildren;i++)
                   {
                       nodCurent->children[i]->lungime=nodCurent->lungime/nodCurent->nrOfChildren;
                       nodCurent->children[i]->centruX=nodCurent->children[i-1]->centruX+nodCurent->children[i]->lungime;
                   }
                }
        }
        for(int i=0;i<nodCurent->nrOfChildren;i++)
            actualizareCoordonateNoduri(nodCurent->children[i],Xcrt);
    }
}

void desenareCatTimp(nod *nodCurent,int adancimeCRT,int adancimeCatTimp)
{
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT,nodCurent->centruX+nodCurent->lungime/2,adancimeCRT);
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT,nodCurent->centruX-nodCurent->lungime/2,adancimeCatTimp);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeCRT,nodCurent->centruX+nodCurent->lungime/2,adancimeCatTimp);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeCatTimp,nodCurent->centruX-nodCurent->lungime/2,adancimeCatTimp);
    setfillstyle(EMPTY_FILL, 0);
    floodfill(nodCurent->centruX+nodCurent->lungime/2-1,adancimeCatTimp+1,COLORS.WHITE);
}

void completareDaca(nod *nodCurent,int adancimeCRT,int adancimeDaca,int adancimeDacaInit,int mare)
{
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeDaca,nodCurent->centruX+nodCurent->lungime/2,adancimeCRT);
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT,nodCurent->centruX+nodCurent->lungime/2,adancimeCRT);
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeDaca,nodCurent->centruX-nodCurent->lungime/2,adancimeCRT);

    if(mare==1)
    {
        setfillstyle(BKSLASH_FILL,15);
        floodfill(nodCurent->centruX-nodCurent->lungime/2+1,adancimeCRT-1,COLORS.WHITE);
    }
    else if(mare==0)
            {
                setfillstyle(BKSLASH_FILL,15);cout<<adancimeCRT<<endl;
                floodfill(nodCurent->centruX+nodCurent->lungime/2-1,adancimeCRT-1,COLORS.WHITE);
            }
}

void desenarePentru(nod *nodCurent,int adancimeCRT,int adancimePentru)
{
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT,nodCurent->centruX+nodCurent->lungime/2,adancimeCRT);
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT,nodCurent->centruX-nodCurent->lungime/2,adancimePentru);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeCRT,nodCurent->centruX+nodCurent->lungime/2,adancimePentru);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimePentru,nodCurent->centruX-nodCurent->lungime/2,adancimePentru);
    setfillstyle(EMPTY_FILL, 0);
    floodfill(nodCurent->centruX+nodCurent->lungime/2-1,adancimePentru+1,COLORS.WHITE);
}

void desenareRepeta(nod *nodCurent,int adancimeCRT,int adancimeRepeta)
{
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT+DIMENSIUNE.repetaLatime,nodCurent->centruX+nodCurent->lungime/2,adancimeCRT+DIMENSIUNE.repetaLatime);
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeCRT+DIMENSIUNE.repetaLatime,nodCurent->centruX-nodCurent->lungime/2,adancimeRepeta);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeCRT+DIMENSIUNE.repetaLatime,nodCurent->centruX+nodCurent->lungime/2,adancimeRepeta);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeRepeta,nodCurent->centruX-nodCurent->lungime/2,adancimeRepeta);
    outtextxy(nodCurent->centruX-3*nodCurent->lungime/8,adancimeCRT+DIMENSIUNE.repetaLatime/2,nodCurent->content);
    setfillstyle(EMPTY_FILL, 0);
    floodfill(nodCurent->centruX+nodCurent->lungime/2-1,adancimeCRT+1,COLORS.WHITE);
}

void actiuneDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocSimplu A;
    A.latime=DIMENSIUNE.actiuneLatime;
    A.lungime=nodCurent->lungime;
    strcpy(A.continut,nodCurent->content);
    A.centru.x=nodCurent->centruX;
    A.centru.y=adancimeCRT+DIMENSIUNE.actiuneLatime/2;
    adancimeCRT=adancimeCRT+DIMENSIUNE.actiuneLatime;
    instructiune(A);
    setfillstyle(EMPTY_FILL, 0);
    floodfill(A.centru.x,A.centru.y,COLORS.WHITE);
}

void dacaDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocDaca D;
    D.chenar.latime=DIMENSIUNE.dacaLatime;
    D.chenar.lungime=nodCurent->lungime;
    strcpy(D.chenar.continut,nodCurent->content);
    D.chenar.centru.x=nodCurent->centruX;
    D.chenar.centru.y=adancimeCRT+DIMENSIUNE.dacaLatime/2;
    D.pozConditie.x=D.chenar.centru.x;
    D.pozConditie.y=D.chenar.centru.y-D.chenar.latime/4;
    D.separare.x=D.chenar.centru.x;
    D.separare.y=D.chenar.centru.y+D.chenar.latime/2;
    daca(D);
}

void catTimpDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocCatTimp T;
    T.lungimeChenar=nodCurent->lungime;
    strcpy(T.conditie,nodCurent->content);
    T.centruChenar.x=nodCurent->centruX;
    T.centruChenar.y=adancimeCRT+DIMENSIUNE.catTimpLatime/2;
    cat_timp(T);
    adancimeCRT=adancimeCRT+DIMENSIUNE.catTimpLatime;
}

void breakDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocIntrerupe B;
    B.chenar.latime=DIMENSIUNE.breakLatime;
    B.chenar.lungime=nodCurent->lungime;
    B.chenar.centru.x=nodCurent->centruX;
    B.chenar.centru.y=adancimeCRT+DIMENSIUNE.breakLatime/2;
    intrerupe(B);
    adancimeCRT=adancimeCRT+DIMENSIUNE.breakLatime;
}

void pentruDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocPentru P;
    P.lungimeChenar=nodCurent->lungime;
    strcpy(P.conditie,nodCurent->content);
    P.centruChenar.x=nodCurent->centruX;
    P.centruChenar.y=adancimeCRT+DIMENSIUNE.pentruLatime/2;
    pentru(P);
    adancimeCRT=adancimeCRT+DIMENSIUNE.pentruLatime;
}

void repetaDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocRepeta R;
    R.lungimeChenar=nodCurent->lungime;
    strcpy(R.conditie,nodCurent->content);
    R.centruChenar.x=nodCurent->centruX;
    R.centruChenar.y=adancimeCRT+DIMENSIUNE.repetaLatime/2;
}

void selectieCazDesen(nod *nodCurent,int &adancimeCRT)
{
    BlocSelectieCaz S;
    S.lungimeChenar=nodCurent->lungime;
    S.latimeChenar=DIMENSIUNE.selectieLatime;
    S.centruChenar.x=nodCurent->centruX;
    S.centruChenar.y=adancimeCRT+DIMENSIUNE.selectieLatime/2;
    S.nrCazuri=nodCurent->nrOfChildren;
    strcpy(S.conditie,nodCurent->content);

    char cazuri[nodCurent->nrOfChildren][BUFFER_SIZE];
    for(int i=0;i<nodCurent->nrOfChildren;i++)
        strcpy(cazuri[i],nodCurent->children[i]->content);

    selectie_caz(S,cazuri);

    adancimeCRT+=DIMENSIUNE.selectieLatime;
}
void completareSelectie(nod *nodCurent,int adancimeSelectieCRT,int adancimeSelectieInit)
{
    line(nodCurent->centruX-nodCurent->lungime/2,adancimeSelectieInit,nodCurent->centruX-nodCurent->lungime/2,adancimeSelectieCRT);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeSelectieInit,nodCurent->centruX+nodCurent->lungime/2,adancimeSelectieCRT);
    line(nodCurent->centruX+nodCurent->lungime/2,adancimeSelectieCRT,nodCurent->centruX-nodCurent->lungime/2,adancimeSelectieCRT);
    int lungime=nodCurent->lungime/nodCurent->nrOfChildren,x=nodCurent->centruX-nodCurent->lungime/2;

    //setfillstyle(SOLID_FILL,CYAN);
    for(int i=0;i<=nodCurent->nrOfChildren;i++)
    {
        line(x,adancimeSelectieCRT,x,adancimeSelectieInit);
        if(i>0)floodfill(x-1,adancimeSelectieCRT-5,COLORS.WHITE);
        x+=lungime;
    }
}
void parcurgereArbore(nod *nodCurent,int &adancimeCRT)
{
    //adancimea curenta (adancimeCRT) se modifica dupa ce desenez un bloc, pentru ca sa stiu sa desenez urmatorul bloc fix dupa cel curent
    if(nodCurent != NULL)
    {
        if(strcmp(nodCurent->typeOfBlock,"ACTION")==0)
            {
            actiuneDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"IF")==0)
            {
                dacaDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"WHILE")==0)
            {
                catTimpDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"BREAK")==0)
            {
                breakDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"FOR")==0)
            {
                pentruDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"DO_WHILE")==0)
            {
                repetaDesen(nodCurent,adancimeCRT);
            }
        else if(strcmp(nodCurent->typeOfBlock,"SELECTIE")==0)
            {
                selectieCazDesen(nodCurent,adancimeCRT);
            }

            int adancimeDacaInit=adancimeCRT+DIMENSIUNE.dacaLatime; //adancimea initiala a blocului DACA
            int adancimeCatTimp=adancimeCRT-DIMENSIUNE.catTimpLatime; //adancimea curenta a ce se afla in interiorul Cat Timp
            int adancimePentru=adancimeCRT-DIMENSIUNE.pentruLatime; //adancimea curenta a ce se afla in interiorul Pentru
            int adancimeDaca; //adancimea curenta a ce se afla in interiorul Daca
            int adancimeRepeta=adancimeCRT; //adancimea curenta a ce se afla in interiorul Repeta
            int adancimeSelectie,adancimeSelectieInit; //adancimea lui SELECTIE
            int adancimeCazMax=0;

    if(strcmp(nodCurent->typeOfBlock,"IF")==0)
            {
                adancimeCRT=adancimeCRT+DIMENSIUNE.dacaLatime;
                adancimeDaca=adancimeCRT-DIMENSIUNE.dacaLatime;
            }


    for(int i=0;i<nodCurent->nrOfChildren;i++)
           {
               if(strcmp(nodCurent->children[i]->typeOfBlock,"ELSE")==0)
               {
                   parcurgereArbore(nodCurent->children[i],adancimeDacaInit); //Pe else se vor desena blocurile incepand cu adancimea initiala a lui daca
               }
               else if(strcmp(nodCurent->children[i]->typeOfBlock,"CAZ")==0)
                   {
                       adancimeSelectie=adancimeCRT;
                       adancimeSelectieInit=adancimeCRT;
                       parcurgereArbore(nodCurent->children[i],adancimeSelectie);
                       if(adancimeCazMax==0 || adancimeCazMax<adancimeSelectie) adancimeCazMax=adancimeSelectie;
                       //cout<<adancimeCazMax<<endl;
                   }
                    else parcurgereArbore(nodCurent->children[i],adancimeCRT); //orice bloc care nu e fiul lui else se va desena incpand cu adancimea curenta, adica se va adauga la finalul figurii
           }

    if(strcmp(nodCurent->typeOfBlock,"SELECTIE")==0)
    {
        adancimeCRT=adancimeCazMax;
        completareSelectie(nodCurent,adancimeCazMax,adancimeSelectieInit);
    }
    if(strcmp(nodCurent->typeOfBlock,"IF")==0)
             {
                    int mare=-1;
                    if(adancimeDacaInit>adancimeCRT)
                    {
                        mare=1;
                        adancimeCRT=adancimeDacaInit;
                    }
                    else if(adancimeDacaInit<adancimeCRT) mare=0;

                    completareDaca(nodCurent,adancimeCRT,adancimeDaca,adancimeDacaInit,mare);
                    //echilibrarea desenului pentru Daca deoarece se poate ca sa am mai multi fii in Else!
             }

    if(strcmp(nodCurent->typeOfBlock,"WHILE")==0)
             {
                desenareCatTimp(nodCurent,adancimeCRT,adancimeCatTimp);
                //chenarul mare a lui Cat Timp il desenez dupa ce i-am desenat toti fii, de aceea am nevoie si de adancimeCatTimp
             }

    if(strcmp(nodCurent->typeOfBlock,"FOR")==0)
             {
                desenarePentru(nodCurent,adancimeCRT,adancimePentru);
                //chenarul mare a lui Pentru il desenez dupa ce i-am desenat toti fii, de aceea am nevoie si de adancimePentru
             }

    if(strcmp(nodCurent->typeOfBlock,"DO_WHILE")==0)
             {
                desenareRepeta(nodCurent,adancimeCRT,adancimeRepeta);
                //chenarul mare a lui Repeta Cat Timp il desenez dupa ce i-am desenat toti fii, de aceea am nevoie si de adancimeRepeta
                adancimeCRT=adancimeCRT+DIMENSIUNE.repetaLatime;
             }
    }
}
int inaltimeArbore(nod *nodCurent)
{
    if(nodCurent->nrOfChildren==0) return 1;
    else
    {
        int max=0;
        for(int i=0;i<nodCurent->nrOfChildren;i++)
        {
            int inaltime_copil=inaltimeArbore(nodCurent->children[i]);
            if(inaltime_copil>max) max=inaltime_copil;//cout<<max;
        }
        if(strcmp(nodCurent->content,"") && strcmp(nodCurent->typeOfBlock,"ELSE")) return max+1;
        else return max;
    }
}
void indiceLungime(nod *nodCurent,int &indiceL)
{
    int max_inaltime=0,max_poz=0,i;

    if(nodCurent!=NULL)
    {
    if(strcmp(nodCurent->content,""))
    {
    if(strcmp(nodCurent->typeOfBlock,"IF")==0) indiceL=indiceL*2;
    else if(strcmp(nodCurent->typeOfBlock,"WHILE")==0 || strcmp(nodCurent->typeOfBlock,"DO_WHILE")==0 || strcmp(nodCurent->typeOfBlock,"FOR")==0) indiceL=indiceL+1;
    else if(strcmp(nodCurent->typeOfBlock,"SELECTIE")==0) indiceL*=nodCurent->nrOfChildren;
    }
    for(i=0;i<nodCurent->nrOfChildren;i++)
        {
            int inaltime_copil=inaltimeArbore(nodCurent->children[i]);
            if(inaltime_copil>max_inaltime)
            {
                max_inaltime=inaltime_copil;
                max_poz=i;
            }
        }
    if(nodCurent->nrOfChildren>0)indiceLungime(nodCurent->children[max_poz],indiceL);
    }
}
void latimetotal(nod* nodCurent,int &latime)
{
    if(nodCurent!=NULL)
    {
        if(strcmp(nodCurent->typeOfBlock,"ELSE"))
        {
        if(strcmp(nodCurent->typeOfBlock,"ACTION")==0)
        {
           latime+=DIMENSIUNE.actiuneLatime;
        }
        else if(strcmp(nodCurent->typeOfBlock,"IF")==0)
            {
                latime+=DIMENSIUNE.dacaLatime;
            }
        else if(strcmp(nodCurent->typeOfBlock,"WHILE")==0)
                {
                   latime+=DIMENSIUNE.catTimpLatime;
                }
                else if(strcmp(nodCurent->typeOfBlock,"BREAK")==0)
                    {
                        latime+=DIMENSIUNE.breakLatime;
                    }
                else if(strcmp(nodCurent->typeOfBlock,"FOR")==0)
                    {
                        latime+=DIMENSIUNE.pentruLatime;
                    }
                else  if(strcmp(nodCurent->typeOfBlock,"DO_WHILE")==0)
                    {
                         latime+=DIMENSIUNE.repetaLatime;
                    }
                else if(strcmp(nodCurent->typeOfBlock,"SELECTIE")==0)
                    {
                        latime+=DIMENSIUNE.selectieLatime;
                    }
        if(strcmp(nodCurent->typeOfBlock,"SELECTIE"))
        for(int i=0;i<nodCurent->nrOfChildren;i++)
            latimetotal(nodCurent->children[i],latime);
        }
    }
}

// FUNCTII PENTRU TESTARE ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

// functia afiseaza continutul nodului actual si dupa merge din parinte in parinte si afieaza continutul
// functie construita pentru testare

void printContentFromNodeToParentPentruTest(nod *nodCurrent)
{
    nod *p = nodCurrent;
    while(p->parent != NULL)
    {
        cout<<p->typeOfBlock<<" | "<<p->content<<" <--- ";
        p = p->parent;
    }
    cout<<endl;
}

// parcurgere fara vizualizare grafica
void parcurgereArboreFaraGraficaPentruTest(nod *&nodCurrent)
{
    if(nodCurrent != NULL)
    {
        if(strcmp(nodCurrent->content, "") != 0)
            printContentFromNodeToParentPentruTest(nodCurrent);


        for(int i=0;i<nodCurrent->nrOfChildren;i++)
            parcurgereArboreFaraGraficaPentruTest(nodCurrent->children[i]);
    }
}

#endif // ARBORE_H_INCLUDED
