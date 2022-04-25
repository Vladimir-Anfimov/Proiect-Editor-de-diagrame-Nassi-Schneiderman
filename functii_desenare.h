#ifndef FUNCTII_DESENARE_H_INCLUDED
#define FUNCTII_DESENARE_H_INCLUDED

void Dreptunghi(punct C,int lungime,int latime)
{
    rectangle(C.x-lungime/2,C.y-latime/2,C.x+lungime/2,C.y+latime/2);
}
void instructiune(BlocSimplu I)
{
  Dreptunghi(I.centru,I.lungime,I.latime);
  outtextxy(I.centru.x-textwidth(I.continut)/2,I.centru.y,I.continut);
}
void daca(BlocDaca D)
{
    char da[3],nu[3];
    strcpy(da,"DA");
    strcpy(nu,"NU");

    Dreptunghi(D.chenar.centru,D.chenar.lungime,D.chenar.latime);
    setfillstyle(EMPTY_FILL, 0);
    floodfill(D.pozConditie.x,D.pozConditie.y,COLORS.WHITE);
    outtextxy(D.pozConditie.x-textwidth(D.chenar.continut)/2,D.pozConditie.y,D.chenar.continut);
    line(D.chenar.centru.x-D.chenar.lungime/2,D.chenar.centru.y-D.chenar.latime/2,D.separare.x,D.separare.y);
    line(D.separare.x,D.separare.y,D.chenar.centru.x+D.chenar.lungime/2,D.chenar.centru.y-D.chenar.latime/2);
    outtextxy(D.separare.x-D.chenar.lungime/4-textwidth(da)/2,D.separare.y-D.chenar.latime/4,da);
    outtextxy(D.separare.x+D.chenar.lungime/4-textwidth(da)/2,D.separare.y-D.chenar.latime/4,nu);
}
void pentru(BlocPentru P)
{
    //Dreptunghi(P.actiune.centru,P.actiune.lungime,P.actiune.latime);
    //Dreptunghi(P.centruChenar,P.lungimeChenar,P.latimeChenar);
    outtextxy(P.centruChenar.x-P.lungimeChenar/4,P.centruChenar.y,P.conditie);
}
void cat_timp(BlocCatTimp T)
{
    outtextxy(T.centruChenar.x-T.lungimeChenar/4,T.centruChenar.y,T.conditie);
}
void repeta(BlocRepeta R)
{
    //Dreptunghi(R.actiune.centru,R.actiune.lungime,R.actiune.latime);
    //Dreptunghi(R.centruChenar,R.lungimeChenar,R.latimeChenar);
    outtextxy(R.centruChenar.x-R.lungimeChenar/3,R.centruChenar.y+3*R.latimeChenar/8,R.conditie);
}
void selectie_caz(BlocSelectieCaz S,char cazuri[20][BUFFER_SIZE])
{
    int i,lungimeCaz,latimeCaz,Xcrt,Ycrt,Ycrt2;
    punct Separare;

    lungimeCaz=S.lungimeChenar/S.nrCazuri;
    latimeCaz=S.latimeChenar/(S.nrCazuri-1);

    Separare.x=S.centruChenar.x-S.lungimeChenar/2+(S.nrCazuri-1)*lungimeCaz;
    Separare.y=S.centruChenar.y+S.latimeChenar/2;

    Xcrt=S.centruChenar.x-S.lungimeChenar/2;
    Ycrt=S.centruChenar.y-S.latimeChenar/2;
    Ycrt2=S.centruChenar.y+S.latimeChenar/2;

    Dreptunghi(S.centruChenar,S.lungimeChenar,S.latimeChenar);

    setfillstyle(EMPTY_FILL,0);
    floodfill(S.centruChenar.x,S.centruChenar.y,COLORS.WHITE);

    line(S.centruChenar.x-S.lungimeChenar/2,S.centruChenar.y-S.latimeChenar/2,Separare.x,Separare.y);
    line(S.centruChenar.x+S.lungimeChenar/2,S.centruChenar.y-S.latimeChenar/2,Separare.x,Separare.y);
    outtextxy(Separare.x-textwidth(S.conditie)/2,Separare.y-3*S.latimeChenar/4,S.conditie);

    char caz[10]="caz ";

    for(i=0;i<S.nrCazuri-1;i++)
        {
            Xcrt+=lungimeCaz;
            Ycrt+=latimeCaz;
            line(Xcrt,Ycrt,Xcrt,Ycrt2);
            outtextxy(Xcrt-3*lungimeCaz/4-textwidth(caz)/2,Ycrt2-textheight(caz)-latimeCaz/8,cazuri[i]);
        }
            outtextxy(Xcrt+3*lungimeCaz/4-textwidth("implicit")/2,Ycrt2-textheight("implicit")-latimeCaz/8,"implicit");
}
void intrerupe(BlocIntrerupe B)
{
    char intrerupe[15];
    strcpy(intrerupe,"intrerupe( )");
    Dreptunghi(B.chenar.centru,B.chenar.lungime,B.chenar.latime);
    setfillstyle(EMPTY_FILL,0);
    floodfill(B.chenar.centru.x,B.chenar.centru.y,COLORS.WHITE);
    outtextxy(B.chenar.centru.x-textwidth(intrerupe)/2,B.chenar.centru.y,intrerupe);
    line(B.chenar.centru.x-3*B.chenar.lungime/8,B.chenar.centru.y-B.chenar.latime/2,B.chenar.centru.x-B.chenar.lungime/2,B.chenar.centru.y);
    line(B.chenar.centru.x-B.chenar.lungime/2,B.chenar.centru.y,B.chenar.centru.x-3*B.chenar.lungime/8,B.chenar.centru.y+B.chenar.latime/2);
}
void desenareButoaneScroll()
{
    setfillstyle(SOLID_FILL, WHITE);
    //desenare sageata sus
    line(WINDOW_WIDTH/2,30,WINDOW_WIDTH/2-50,60);
    line(WINDOW_WIDTH/2,40,WINDOW_WIDTH/2-50,70);
    line(WINDOW_WIDTH/2-50,60,WINDOW_WIDTH/2-50,70);
    line(WINDOW_WIDTH/2,30,WINDOW_WIDTH/2+50,60);
    line(WINDOW_WIDTH/2,40,WINDOW_WIDTH/2+50,70);
    line(WINDOW_WIDTH/2+50,60,WINDOW_WIDTH/2+50,70);
    floodfill(WINDOW_WIDTH/2,32,COLORS.WHITE);

    //desenare sageteata jos
    line(WINDOW_WIDTH/2+50,1020,WINDOW_WIDTH/2,1050);
    line(WINDOW_WIDTH/2+50,1010,WINDOW_WIDTH/2,1040);
    line(WINDOW_WIDTH/2+50,1010,WINDOW_WIDTH/2+50,1020);
    line(WINDOW_WIDTH/2-50,1020,WINDOW_WIDTH/2,1050);
    line(WINDOW_WIDTH/2-50,1010,WINDOW_WIDTH/2,1040);
    line(WINDOW_WIDTH/2-50,1010,WINDOW_WIDTH/2-50,1020);
    floodfill(WINDOW_WIDTH/2,1042,COLORS.WHITE);

    //desenare sageata dreapta
    line(1900,540,1850,510);
    line(1880,540,1830,510);
    line(1830,510,1850,510);
    line(1900,540,1850,570);
    line(1880,540,1830,570);
    line(1830,570,1850,570);
    floodfill(1899,540,COLORS.WHITE);

    //desenare sageata stanga
    line(20,540,70,510);
    line(40,540,90,510);
    line(70,510,90,510);
    line(20,540,70,570);
    line(40,540,90,570);
    line(70,570,90,570);
    floodfill(21,540,COLORS.WHITE);


}
void desenareButoaneZoom()
{
    //desenez +
    int poly_plus1[8]={
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/50,
    WINDOW_HEIGHT/25,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/50,
    WINDOW_HEIGHT/20+2*WINDOW_HEIGHT/50+WINDOW_HEIGHT/20+WINDOW_HEIGHT/50-WINDOW_HEIGHT/25,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20-WINDOW_WIDTH/50,
    WINDOW_HEIGHT/20+2*WINDOW_HEIGHT/50+WINDOW_HEIGHT/20+WINDOW_HEIGHT/50-WINDOW_HEIGHT/25,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20-WINDOW_WIDTH/50,
    WINDOW_HEIGHT/25};
    int poly_plus2[8]={
    WINDOW_WIDTH-WINDOW_WIDTH/15,
    WINDOW_HEIGHT/20+WINDOW_HEIGHT/50,
    WINDOW_WIDTH-WINDOW_WIDTH/15,
    WINDOW_HEIGHT/20+2*WINDOW_HEIGHT/50,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20,
    WINDOW_HEIGHT/20+2*WINDOW_HEIGHT/50,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20,
    WINDOW_HEIGHT/20+WINDOW_HEIGHT/50,};

    setfillstyle(SOLID_FILL,WHITE);

    fillpoly(4,poly_plus1);
    fillpoly(4,poly_plus2);

    //desenez -
    int poly_minus[8]={
    WINDOW_WIDTH-WINDOW_WIDTH/15,
    WINDOW_HEIGHT/7,
    WINDOW_WIDTH-WINDOW_WIDTH/15,
    WINDOW_HEIGHT/6,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20,
    WINDOW_HEIGHT/6,
    WINDOW_WIDTH-WINDOW_WIDTH/15+WINDOW_WIDTH/20,
    WINDOW_HEIGHT/7,
    };

    fillpoly(4,poly_minus);
}
void desenareButonVizualizareCod()
{
    int auxColor=getcolor(),auxBkColor=getbkcolor();
    setbkcolor(CYAN);
    setcolor(WHITE);
    bar3d(WINDOW_WIDTH/9,WINDOW_HEIGHT/100,WINDOW_WIDTH/4,WINDOW_HEIGHT/15,10,1);
    setbkcolor(WHITE);
    setcolor(CYAN);
    settextstyle(BOLD_FONT,0,3);
    outtextxy(2*WINDOW_WIDTH/11-textwidth("VIZUALIZARE COD")/2,WINDOW_HEIGHT/30-textheight("VIZUALIZARE COD")/2,"VIZUALIZARE COD");
    setbkcolor(auxBkColor);
    setcolor(auxColor);
}
void desenareButonInapoi()
{
    //desenare buton BACK
    int auxColor=getcolor(),auxBkColor=getbkcolor();
    setbkcolor(CYAN);
    setcolor(WHITE);
    bar3d(WINDOW_WIDTH/100,WINDOW_HEIGHT/100,WINDOW_WIDTH/10,WINDOW_HEIGHT/15,10,1);
    setbkcolor(WHITE);
    setcolor(CYAN);
    settextstyle(BOLD_FONT,0,3);
    outtextxy(5*WINDOW_WIDTH/100-textwidth("INAPOI")/2,WINDOW_HEIGHT/30-textheight("INAPOI")/2,"INAPOI");
    setbkcolor(auxBkColor);
    setcolor(auxColor);
}
void desenareButonInapoiDiagrama()
{
    int auxColor=getcolor(),auxBkColor=getbkcolor();
    setbkcolor(CYAN);
    setcolor(WHITE);
    bar3d(WINDOW_WIDTH/9,WINDOW_HEIGHT/100,WINDOW_WIDTH/4,WINDOW_HEIGHT/15,10,1);
    setbkcolor(WHITE);
    setcolor(CYAN);
    settextstyle(BOLD_FONT,0,3);
    outtextxy(2*WINDOW_WIDTH/11-textwidth("DIAGRAMA")/2,WINDOW_HEIGHT/30-textheight("DIAGRAMA")/2,"DIAGRAMA");
    setbkcolor(auxBkColor);
    setcolor(auxColor);
}
void desenareSagetiVC()
{
    int auxColor=getcolor(),auxBkColor=getbkcolor();
    setbkcolor(CYAN);
    setcolor(WHITE);

    //sageata sus vizualizare_cod
    int poly1[6]={1830,480,1780,560,1880,560};
    int poly2[6]={1880,570,1780,570,1830,650};
    fillpoly(3,poly1);
    fillpoly(3,poly2);
    setbkcolor(auxBkColor);
    setcolor(auxColor);
}
void desenare_mesaj(char mesaj_eroare[])
{
    char *p;
    int y=400;
    p=strtok(mesaj_eroare,".");
    while(p!=NULL)
    {
        outtextxy(600,y,p);
        y+=50;
        p=strtok(NULL,".");
    }
}
void desenareEroare(char mesaj_eroare[])
{
    clearviewport();
    setbkcolor(RED);
    settextstyle(BOLD_FONT,0,4);
    readimagefile("e.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    desenareButonInapoi();
    desenare_mesaj(mesaj_eroare);

    bool gata=false;
    do
    {
    if(ismouseclick(WM_LBUTTONDOWN))
     {

     clearmouseclick(WM_LBUTTONDOWN);

     int x=mousex();
     int y=mousey();

     if(x>=WINDOW_WIDTH/100 && x<=WINDOW_WIDTH/10 && y>=WINDOW_HEIGHT/100 && y<=WINDOW_HEIGHT/15) gata=true;
      }
    }
    while(!gata);
    clearviewport();

}
void desenare_borduri()
{
    int auxBkColor = getbkcolor();
    int auxColor=getcolor();

    setbkcolor(CYAN);
    setfillstyle(CLOSE_DOT_FILL, COLORS.LIGHTBLUE);
    setcolor(COLORS.CYAN);

    int bordura_dreapta[8]={WINDOW_WIDTH-WINDOW_WIDTH/10, 0, WINDOW_WIDTH-WINDOW_WIDTH/10, WINDOW_HEIGHT, WINDOW_WIDTH,WINDOW_HEIGHT, WINDOW_WIDTH, 0};
    int bordura_stanga[8]={0,0,0,WINDOW_HEIGHT,WINDOW_WIDTH/10,WINDOW_HEIGHT,WINDOW_WIDTH/10,0};
    int bordura_sus[8]={0, 0, 0, WINDOW_WIDTH/12, WINDOW_WIDTH, WINDOW_WIDTH/12, WINDOW_WIDTH, 0};
    int bordura_jos[8]={0,WINDOW_HEIGHT-WINDOW_WIDTH/12,0,WINDOW_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT-WINDOW_WIDTH/12};
    fillpoly(4,bordura_dreapta);
    fillpoly(4,bordura_stanga);
    fillpoly(4,bordura_sus);
    fillpoly(4,bordura_jos);

    setbkcolor(auxBkColor);
    setfillstyle(SOLID_FILL, COLORS.WHITE);
    setcolor(auxColor);
}
void desenare_background_cod()
{
    //int auxBkColor = getbkcolor();
    int poly[8]={
    WINDOW_WIDTH/10,
    WINDOW_WIDTH/12,
    WINDOW_WIDTH/10,
    WINDOW_HEIGHT-WINDOW_WIDTH/12,
    WINDOW_WIDTH-WINDOW_WIDTH/10,
    WINDOW_HEIGHT-WINDOW_WIDTH/12,
    WINDOW_WIDTH-WINDOW_WIDTH/10,
    WINDOW_WIDTH/12
    };

    fillpoly(4,poly);
    //setbkcolor(auxBkColor);
}
#endif // FUNCTII_DESENARE_H_INCLUDED
