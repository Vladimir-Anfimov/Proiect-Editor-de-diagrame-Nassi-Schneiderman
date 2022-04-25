#ifndef PARCURGERE_PSEUDOCOD_H_INCLUDED
#define PARCURGERE_PSEUDOCOD_H_INCLUDED

#include <cstring>
#include "arbore.h"
#include "compilare_pseudocod.h"

using namespace std;

struct BLOCK_TYPES_STRUCT {
    char ACTION[10] = ";";
    char IF[10] = "daca";
    char ELSE[10] = "altfel";
    char FOR[10] = "pentru";
    char WHILE[10] = "cat";
    char DO_WHILE[10] = "repeta";
    char SELECTION_CASE[10] = "selectati";
    char CASE[10] = "caz";
    char BREAK[15] = "intrerupe()";
} BLOCK_TYPES;

void prelucrareAction(char buffer[], nod *&nodCurrent)
{
    buffer[strlen(buffer)-1] = '\0';
    trim(buffer);
    addNewChild(nodCurrent, buffer, "ACTION");
}
void prelucrareIf(char buffer[], nod *&nodCurrent)
{
    extragereConditie(buffer);
    trim(buffer);
    addNewChild(nodCurrent, buffer, "IF");
}
void prelucrareElse(nod *&nodCurrent)
{
    goInLastOne(nodCurrent);
    addNewChild(nodCurrent, "altfel", "ELSE");
}
void prelucrareFor(char buffer[], nod *&nodCurrent)
{
    extragereConditie(buffer);
    trim(buffer);
    char Buffer[BUFFER_SIZE];
    strcpy(Buffer,"pentru ");
    strcat(Buffer,buffer);
    addNewChild(nodCurrent, Buffer, "FOR");
}
void prelucrareWhile(char buffer[], nod *&nodCurrent)
{
    extragereConditie(buffer);
    trim(buffer);
    strcat(buffer,"?");
    addNewChild(nodCurrent, buffer, "WHILE");
}
void prelucrareDoWhileFirstStep(nod *&nodCurrent)
{
    addNewChild(nodCurrent, "__WAITING_FOR_CONTENT__", "DO_WHILE");
}
void prelucrareDoWhileSecondStep(char buffer[], nod *&nodCurrent)
{
    goBackToParent(nodCurrent);
    extragereConditie(buffer);
    trim(buffer);
    strcat(buffer,"?");
    strcpy(nodCurrent->children[nodCurrent->nrOfChildren - 1]->content, buffer);
}
void prelucrareSelectionCase(char buffer[], nod *&nodCurrent)
{
    extragereConditie(buffer);
    trim(buffer);
    char Buffer[BUFFER_SIZE] = "selectati cazul ";
    strcat(Buffer,buffer);
    addNewChild(nodCurrent, Buffer, "SELECTIE");
}
void prelucrareCase(char buffer[], nod *&nodCurrent)
{
    extragereConditie(buffer);
    trim(buffer);
    char Buffer[BUFFER_SIZE] = "caz ";
    strcat(Buffer,buffer);
    addNewChild(nodCurrent, Buffer, "CAZ");
}
void prelucrareBreak(char buffer[], nod *&nodCurrent)
{
    buffer[strlen(buffer)-1] = '\0';
    trim(buffer);
    addNewChild(nodCurrent, buffer, "BREAK");
}
void actualizareDimensiuni(Dimensiuni &Dimensiune,float indiceZoom,int LUNGIMEinit)
{
             DIMENSIUNE.lungime=LUNGIMEinit*indiceZoom;
             DIMENSIUNE.dacaLatime=DACA_LATIME*indiceZoom;
             DIMENSIUNE.breakLatime=BREAK_LATIME*indiceZoom;
             DIMENSIUNE.catTimpLatime=CAT_TIMP_LATIME*indiceZoom;
             DIMENSIUNE.repetaLatime=REPETA_LATIME*indiceZoom;
             DIMENSIUNE.actiuneLatime=ACTIUNE_LATIME*indiceZoom;
             DIMENSIUNE.pentruLatime=PENTRU_LATIME*indiceZoom;
             DIMENSIUNE.selectieLatime=SELECTIE_LATIME*indiceZoom;
}
void initializareDimensiuni(Dimensiuni &Dimensiune)
{
             DIMENSIUNE.lungime=LUNGIME;
             DIMENSIUNE.dacaLatime=DACA_LATIME;
             DIMENSIUNE.breakLatime=BREAK_LATIME;
             DIMENSIUNE.catTimpLatime=CAT_TIMP_LATIME;
             DIMENSIUNE.repetaLatime=REPETA_LATIME;
             DIMENSIUNE.actiuneLatime=ACTIUNE_LATIME;
             DIMENSIUNE.pentruLatime=PENTRU_LATIME;
             DIMENSIUNE.selectieLatime=SELECTIE_LATIME;
}
void citireSiPrelucrare(nod *&nodCurent,int Ycrt,int Xcrt)
{
    ifstream fin("algoritm_in_pseudocod.txt");
    nodCurent = new nod;
    char buffer[BUFFER_SIZE];

    while(fin.getline(buffer, BUFFER_SIZE))
    {
        if(strstr(buffer, "{")) goInLastOne(nodCurent);
        else if(strstr(buffer, "}") && strstr(buffer, BLOCK_TYPES.WHILE)) {prelucrareDoWhileSecondStep(buffer, nodCurent);}

        else if(strstr(buffer, "}"))
        {
            if(strcmp(nodCurent->typeOfBlock, "ELSE") == 0) goBackToParent(nodCurent);
            goBackToParent(nodCurent);
        }

        else if(strstr(buffer, BLOCK_TYPES.BREAK)) prelucrareBreak(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.ACTION)) prelucrareAction(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.ELSE)) prelucrareElse(nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.IF)) prelucrareIf(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.FOR)) prelucrareFor(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.WHILE)) prelucrareWhile(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.DO_WHILE)) prelucrareDoWhileFirstStep(nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.SELECTION_CASE)) prelucrareSelectionCase(buffer, nodCurent);

        else if(strstr(buffer, BLOCK_TYPES.CASE)) prelucrareCase(buffer, nodCurent);
    }

    int indiceL=1,latimeTotal=0;

    indiceLungime(nodCurent,indiceL);        //calculez indiceL astfel incat cel mai mic bloc sa aiba lungimea=(const) LUNGIME
    latimetotal(nodCurent,latimeTotal);      //calculez latimea totala a diagramei
    DIMENSIUNE.centruY=Ycrt-latimeTotal/2;   //aici centrez diagrama pe centrul ferestrei de desenat

    DIMENSIUNE.lungime=LUNGIME*indiceL;
    actualizareCoordonateNoduri(nodCurent,Xcrt);

    fin.close();

   // parcurgereArboreFaraGraficaPentruTest(nodCurent);
}
void deseneazaOutputCompliare(RaspunsCompilare raspComp)
{
    const int left = 1100, top = 25, right = 1700, bottom = 150;
    bar3d(left, top, right, bottom, 10, 1);

    int auxColor = getcolor();
    int auxBkColor = getbkcolor();
    setcolor(COLORS.CYAN);
    setbkcolor(COLORS.WHITE);
    outtextxy(left+5, top+3, "ALGORITMUL AFISEAZA:");
    settextstyle(BOLD_FONT,0,2);
    afisare_output(raspComp.mesaj, 590, left+5, top+30);
    setcolor(auxColor);
    setbkcolor(auxBkColor);
}
void desenareDiagrama(nod *nodCurent,int Ycrt,int Xcrt)
{
    int latimeTotal=0;

    latimetotal(nodCurent,latimeTotal); //calculez latimea toatala a diagramei
    DIMENSIUNE.centruY=Ycrt-latimeTotal/2; //centrez diagrama

    int adancimeCRT=DIMENSIUNE.centruY;
    actualizareCoordonateNoduri(nodCurent,Xcrt);
    parcurgereArbore(nodCurent,adancimeCRT);
}
void zoom(nod *nodCurent,float indiceZoom,int &charsize,int &LUNGIMEinit,int Xcrt,int &Ycrt,Dimensiuni &DIMENSIUNE, bool compileaza, RaspunsCompilare raspComp)
{
    //functie pentru zoom
    //zoom-ul se face in functie de acel indiceZoom si se redeseneaza diagrama
    settextstyle(0,0,charsize*indiceZoom);
    actualizareDimensiuni(DIMENSIUNE,indiceZoom,LUNGIMEinit);
    clearviewport();
    readimagefile("bg_diagrama.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    desenareDiagrama(nodCurent,Ycrt,Xcrt);
    desenare_borduri();
    desenareButoaneZoom();
    desenareButoaneScroll();
    desenareButonInapoi();
    desenareButonVizualizareCod();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(compileaza) deseneazaOutputCompliare(raspComp);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void scroll(nod *nodCurent,int Xcrt,int Ycrt, bool compileaza, RaspunsCompilare raspComp,int charsize)
{
    //functie pentru scroll care se face prin sageti
    //se deseneaza din nou dupa ce se modifica centrul digramei : coordonata x(Xcrt) resprectiv coordonata y(Ycrt) in fuctie de sageata, acestea se modifica inainte de a apela functia

    clearviewport();
    readimagefile("bg_diagrama.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    settextstyle(0,0,charsize);cout<<endl<<charsize;
    desenareDiagrama(nodCurent,Ycrt,Xcrt);
    desenare_borduri();
    desenareButoaneZoom();
    desenareButoaneScroll();
    desenareButonInapoi();
    desenareButonVizualizareCod();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(compileaza) deseneazaOutputCompliare(raspComp);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //settextstyle(0,0,1);
}
int vizualizare_cod()
{
    int x=WINDOW_WIDTH/2-200;
    int y=WINDOW_HEIGHT/4;
    int linia1,linia2,linii_permise=24,linie=1;
    bool changed=0;
    char buffer[BUFFER_SIZE],nrlinie[5];
    int rtr=1;
    int auxColor = getcolor();
    int auxBkColor = getbkcolor();

    linia1=1;
    linia2=24;

    setbkcolor(WHITE);
    desenare_borduri();
    setcolor(COLORS.CYAN);
    desenareButonInapoi();
    desenareButonInapoiDiagrama();
    desenareSagetiVC();

    settextstyle(4,0,4);

    linie=1;
    ifstream fin("algoritm_in_pseudocod.txt");
    x=WINDOW_WIDTH/4;
    y=WINDOW_HEIGHT/6;
    desenare_background_cod();
    while(fin.getline(buffer,BUFFER_SIZE) && linie<linia1+linii_permise)
    {
        if(linie>=linia1 && linie<=linia2)
        {
            numar_in_char(linie,nrlinie);
            strcat(nrlinie,".");
            outtextxy(x-80,y,nrlinie);
            outtextxy(x,y,buffer);
            y+=30;
        }
        linie++;
    }
    fin.close();

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
     {
     clearmouseclick(WM_LBUTTONDOWN);
     int Xmouse=mousex();
     int Ymouse=mousey();


    if(Xmouse>=WINDOW_WIDTH/100 && Xmouse<=WINDOW_WIDTH/10 && Ymouse>=WINDOW_HEIGHT/100 && Ymouse<=WINDOW_HEIGHT/15) rtr=0; // buton: ma inorc in meniu, "INAPOI"
    else if(Xmouse>=WINDOW_WIDTH/9 && Xmouse<=WINDOW_WIDTH/4 && Ymouse>=WINDOW_HEIGHT/100 && Ymouse<=WINDOW_HEIGHT/15) rtr=2; // buton: ma intorc la diagrama, "DIAGRAMA"
    else if(Xmouse>=1780 && Xmouse<=1880)
        {
            if(Ymouse>=480 && Ymouse<=560) { linia1++; linia2++; changed=1;}
            else if(Ymouse>=570 && Ymouse<=650)
                {
                    if(linia1>1) {
                            linia1--;
                            linia2--;
                            changed=1;
                            }
                }

            if(changed==1)
            {
            linie=1;
            ifstream fin("algoritm_in_pseudocod.txt");
            x=WINDOW_WIDTH/4;
            y=WINDOW_HEIGHT/6;
            desenare_background_cod();
            while(fin.getline(buffer,BUFFER_SIZE) && linie<linia1+linii_permise)
            {
                if(linie>=linia1 && linie<=linia2)
                {
                numar_in_char(linie,nrlinie);
                strcat(nrlinie,".");
                outtextxy(x-80,y,nrlinie);
                outtextxy(x,y,buffer);
                y+=30;
                }
                linie++;
            }
            fin.close();
            }
            changed=0;
        }
     }
    }
    while(rtr==1);

    clearviewport();

    setcolor(auxColor);
    setbkcolor(auxBkColor);
    //settextstyle(0,0,1);

    return rtr;
}
void redesenare(nod *nodCurent,int Xcrt,int Ycrt, RaspunsCompilare raspComp, bool compileaza)
{
    float indiceZoom=1;
    bool gata=false;
    int charsize=1;
    int LUNGIMEinit;

    LUNGIMEinit=DIMENSIUNE.lungime;
    clearviewport();
    readimagefile("bg_diagrama.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    desenareDiagrama(nodCurent,Ycrt,Xcrt);
    desenare_borduri();
    desenareButoaneZoom();
    desenareButoaneScroll();
    desenareButonInapoi();
    desenareButonVizualizareCod();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(compileaza) deseneazaOutputCompliare(raspComp);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    settextstyle(0,0,1);

    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
     {
     clearmouseclick(WM_LBUTTONDOWN);
     int x=mousex();
     int y=mousey();

     if(x>=WINDOW_WIDTH-WINDOW_WIDTH/15 && x<=WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20 && y>=WINDOW_HEIGHT/25 && y<=WINDOW_HEIGHT/20+2*WINDOW_HEIGHT/50+WINDOW_HEIGHT/20+WINDOW_HEIGHT/50-WINDOW_HEIGHT/25)
     {
                 //Zoom IN
                if(indiceZoom<1.9 && indiceZoom>0)
                {

                    indiceZoom+=0.1;charsize=1;
                    zoom(nodCurent,indiceZoom,charsize,LUNGIMEinit,Xcrt,Ycrt,DIMENSIUNE,compileaza,raspComp);
                }
     }
     else if(x>=WINDOW_WIDTH-WINDOW_WIDTH/15 && x<=WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20 && y>= WINDOW_HEIGHT/7 && y<=WINDOW_HEIGHT/6)
         {
              //Zoom OUT
             if(indiceZoom>=0.7)
             {
                 indiceZoom-=0.1;charsize=1;
                zoom(nodCurent,indiceZoom,charsize,LUNGIMEinit,Xcrt,Ycrt,DIMENSIUNE,compileaza,raspComp);
             }
         }
         else if(x>=WINDOW_WIDTH/2-50 && x<=WINDOW_WIDTH/2+50 && y>=30 && y<=70)
             {
                 //sageata sus
                 Ycrt-=50;
                 charsize=indiceZoom*1;
                 scroll(nodCurent,Xcrt,Ycrt,compileaza,raspComp,charsize);
             }
        else if(x>=WINDOW_WIDTH/2-50 && x<=WINDOW_WIDTH/2+50 && y>=1010 && y<=1050)
             {
                 //sageata jos
                 Ycrt+=50;
                 charsize=indiceZoom*1;
                 scroll(nodCurent,Xcrt,Ycrt,compileaza,raspComp,charsize);
             }
        else if(x>=1830 && x<=1900 && y>=WINDOW_HEIGHT/2-30 && y<=WINDOW_HEIGHT/2+30)
             {
                //sageatadreapta
                Xcrt+=50;
                charsize=indiceZoom*1;
                scroll(nodCurent,Xcrt,Ycrt,compileaza,raspComp,charsize);
             }
        else if(x>=20 && x<=90 && y>=WINDOW_HEIGHT/2-30 && y<=WINDOW_HEIGHT/2+30)
             {
                //sageata stanga
                Xcrt-=50;
                charsize=indiceZoom*1;
                scroll(nodCurent,Xcrt,Ycrt,compileaza,raspComp,charsize);
             }
        else if(x>=WINDOW_WIDTH/9 && x<=WINDOW_WIDTH/4 && y>=WINDOW_HEIGHT/100 && y<=WINDOW_HEIGHT/15 )
            {
                int rtr=vizualizare_cod();
                if(rtr==0) gata=true;
                else if(rtr==2)
                    {
                        LUNGIMEinit=DIMENSIUNE.lungime;
                        clearviewport();
                        readimagefile("bg_diagrama.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                        settextstyle(0,0,charsize);
                        desenareDiagrama(nodCurent,Ycrt,Xcrt);
                        desenare_borduri();
                        desenareButoaneZoom();
                        desenareButoaneScroll();
                        desenareButonInapoi();
                        desenareButonVizualizareCod();
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        if(compileaza) deseneazaOutputCompliare(raspComp);
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
            }
            else if(x>=WINDOW_WIDTH/100 && x<=WINDOW_WIDTH/10 && y>=WINDOW_HEIGHT/100 && y<=WINDOW_HEIGHT/15) gata=true;

     }
    }
    while(!gata);
    clearviewport();
}
int startDesenareDiagramaSimpla()
{
    int Ycrt,Xcrt;
    nod *nodCurent;
    RaspunsCompilare raspComp;

    //initial,centrul diagramei este si centru ferestrei de desenat
    Ycrt=CENTRE_Y;
    Xcrt=CENTRE_X;

    setbkcolor(COLORS.CYAN);
    settextstyle(0,0,1);

    //prima desenare a diagramei fara a se apasa pe vreunul dintre butoane
    initializareDimensiuni(DIMENSIUNE);
    citireSiPrelucrare(nodCurent,Ycrt,Xcrt);

    redesenare(nodCurent,Xcrt,Ycrt,raspComp,false);

    return 0;
}
int startDesenareDiagramaCuExecutie()
{
    int Ycrt,Xcrt;
    nod *nodCurent;
    RaspunsCompilare raspComp;

    char mesaj_eroare[1000];

    //initial,centrul diagramei este si centru ferestrei de desenat
    Ycrt=CENTRE_Y;
    Xcrt=CENTRE_X;

     setbkcolor(COLORS.CYAN);
    //setcolor(COLORS.BLUE);
    settextstyle(0,0,1);

    //prima desenare a diagramei fara a se apasa pe vreunul dintre butoane
    initializareDimensiuni(DIMENSIUNE);

    if(verificare_cod(mesaj_eroare))
    {
        citireSiPrelucrare(nodCurent,Ycrt,Xcrt);
        startCompilare(nodCurent,raspComp);
        redesenare(nodCurent,Xcrt,Ycrt,raspComp,true);
    }
    else{
        desenareEroare(mesaj_eroare);
    }

    return 0;
}

#endif // PARCURGERE_PSEUDOCOD_H_INCLUDED
