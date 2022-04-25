#ifndef INSTRUCTIUNI_GRAFICA_H_INCLUDED
#define INSTRUCTIUNI_GRAFICA_H_INCLUDED

const char PATH_BG_INSTRUCTIUNI[] = "bg_instructiuni.jpg";

const int BTN_WIDTH = 600;
const int CASETA_WIDTH = 400;
const int CASETA_HEIGHT = 300;
const int INSTRUCTIUNI_FONT = BOLD_FONT;


void drawBackButton()
{
    setbkcolor(COLORS.BLUE);
    setfillstyle(EMPTY_FILL, 0);
    bar3d(
            WINDOW_WIDTH/2 - BTN_WIDTH/2,
            900,
            WINDOW_WIDTH/2 + BTN_WIDTH/2,
            900 + 100,
            20,
            1
         );
    setfillstyle(EMPTY_FILL, 0);
    floodfill(
                  WINDOW_WIDTH/2,
                  890,
                  COLORS.WHITE
              );


    floodfill(
                  WINDOW_WIDTH/2 + BTN_WIDTH/2 + 10,
                  950,
                  COLORS.WHITE
              );

    settextstyle(DEFAULT_FONT,HORIZ_DIR, 4);
    outtextxy(
                  WINDOW_WIDTH/2 - textwidth("INAPOI")/2,
                  950 - textheight("INAPOI")/2,
                  "INAPOI"
              );

}

void drawCaseta(int x, int y)
{
    int xLeft = x - CASETA_WIDTH/2, xRight = y - CASETA_HEIGHT/2;
    int yBottom = x + CASETA_WIDTH/2, yTop = y + CASETA_HEIGHT/2;
    setfillstyle(EMPTY_FILL, 0);
    bar3d(xLeft, xRight, yBottom, yTop, 10, 1);
}

void drawTextOne(int x, int y)
{
    settextstyle(DEFAULT_FONT,0,3);
    char text[]="ACTIUNE";
    outtextxy(x - textwidth(text)/2, y - 75, text);

    settextstyle(INSTRUCTIUNI_FONT,0,2);
    BlocSimplu bloc;
    bloc.centru.x = x;
    bloc.centru.y = y+25;
    strcpy(bloc.continut, "");
    bloc.lungime = CASETA_WIDTH - 100;
    bloc.latime = CASETA_HEIGHT - 175;
    setfillstyle(SOLID_FILL, COLORS.MAGENTA);
    instructiune(bloc);
    floodfill(x,y+25,COLORS.WHITE);
    int auxBkColor = getbkcolor();
    setbkcolor(COLORS.MAGENTA);
    outtextxy(bloc.centru.x - textwidth("init(a,b)")/2, bloc.centru.y, "init(a,b)");
    setbkcolor(auxBkColor);
}

void drawTextTwo(int x, int y)
{
    settextstyle(DEFAULT_FONT,0,3);
    char text[]="DACA";
    outtextxy(x - textwidth(text)/2, y - 75, text);

    settextstyle(INSTRUCTIUNI_FONT,0,2);
    BlocSimplu bloc;
    bloc.centru.x = x;
    bloc.centru.y = y+25;
    strcpy(bloc.continut, "");
    bloc.lungime = CASETA_WIDTH - 100;
    bloc.latime = CASETA_HEIGHT - 175;
    instructiune(bloc);
    setfillstyle(SOLID_FILL, COLORS.MAGENTA);
    floodfill(x,y+25,COLORS.WHITE);
    line(
             bloc.centru.x - bloc.lungime/2,
             bloc.centru.y - bloc.latime/2,
             bloc.centru.x,
             bloc.centru.y+bloc.latime/2
        );
    line(
             bloc.centru.x + bloc.lungime/2,
             bloc.centru.y - bloc.latime/2,
             bloc.centru.x,
             bloc.centru.y+bloc.latime/2
        );

    int auxColor = getbkcolor();
    setbkcolor(COLORS.MAGENTA);
    outtextxy(bloc.centru.x - textwidth("mic(a,b)")/2, y, "mic(a,b)");
    outtextxy(bloc.centru.x - 115 - textwidth("Da")/2, bloc.centru.y, "Da");
    outtextxy(bloc.centru.x + 115 - textwidth("Nu")/2, bloc.centru.y, "Nu");


    setbkcolor(auxColor);
}

void drawTextThree(int x, int y)
{
    settextstyle(DEFAULT_FONT,0,3);
    char text[]="CAT TIMP";
    outtextxy(x - textwidth(text)/2, y - 75, text);

    settextstyle(INSTRUCTIUNI_FONT,0,2);
    BlocSimplu bloc;
    bloc.centru.x = x;
    bloc.centru.y = y+25;
    strcpy(bloc.continut, "");
    bloc.lungime = CASETA_WIDTH - 100;
    bloc.latime = CASETA_HEIGHT - 175;
    instructiune(bloc);
    setfillstyle(SOLID_FILL, COLORS.MAGENTA);
    floodfill(x,y+25,COLORS.WHITE);
    line(x - bloc.lungime/2 + 50, y+10, x + bloc.lungime/2, y+10);
    line(x - bloc.lungime/2 + 50, y+10, x - bloc.lungime/2 + 50, y+bloc.latime/2+25);
    int auxColor = getbkcolor();
    setbkcolor(COLORS.MAGENTA);
    outtextxy(x - textwidth("mare(a,b)")/2, y - 20, "mare(a,b)");
    outtextxy(x - textwidth("dif(a,b)")/2 + 10, y + 40, "dif(a,b)");
    setbkcolor(auxColor);
}

void drawTextFour(int x, int y)
{
    settextstyle(DEFAULT_FONT,0,3);
    char text[]="REPETA CAT TIMP";
    outtextxy(x - textwidth(text)/2, y - 75, text);

    settextstyle(INSTRUCTIUNI_FONT,0,2);
    BlocSimplu bloc;
    bloc.centru.x = x;
    bloc.centru.y = y+25;
    strcpy(bloc.continut, "");
    bloc.lungime = CASETA_WIDTH - 100;
    bloc.latime = CASETA_HEIGHT - 175;
    instructiune(bloc);
    setfillstyle(SOLID_FILL, COLORS.MAGENTA);
    floodfill(x,y+25,COLORS.WHITE);
    line(
             x - bloc.lungime/2 + 50,
             y+bloc.latime/2 - 20,
             x + bloc.lungime/2,
             y+bloc.latime/2 - 20
         );
    line(
             x - bloc.lungime/2 + 50,
             y - bloc.latime/2 + 25,
             x - bloc.lungime/2 + 50,
             y+bloc.latime/2 - 20
         );

    int auxColor = getbkcolor();
    setbkcolor(COLORS.MAGENTA);
    outtextxy(x - textwidth("dif(a,b)")/2, y, "dif(a,b)");
    outtextxy(x - textwidth("egal(a,b)")/2 + 10, y + 60, "egal(a,b)");
    setbkcolor(auxColor);

}

void drawTextFive(int x, int y)
{
    char primitive[20][20] = {
        "incr(a)",
        "decr(a)",
        "sum(a,b)",
        "dif(a,b)",
        "prod(a,b)",
        "imp(a,b)",
        "exp(a,b)",
        "afiseaza(a)",
        "mod(a,b)",
        "egal(a,b)",
        "inegal(a,b)",
        "mare(a,b)",
        "mic(a,b)",
        "mareg(a,b)",
        "micg(a,b)",
        "si(a,b)",
        "sau(a,b)",
        "neg(a)",
        "init(a,b)",
        "muta(a,b)"
    };

    int startX = x - CASETA_WIDTH/2 + 15;
    int startY = y - CASETA_HEIGHT/3 + 10;
    int indice=0;
    for(int j=0;j<8;j++, indice++)
        outtextxy(startX, startY + j*25, primitive[indice]);
    for(int j=0;j<6;j++, indice++)
        outtextxy(startX + 125, startY + j*25, primitive[indice]);
    for(int j=0;j<6;j++, indice++)
        outtextxy(startX + 265, startY + j*25, primitive[indice]);
}

void drawTextSix(int x, int y)
{
    settextstyle(INSTRUCTIUNI_FONT,0,3);
    char exempluCod[20][20] = {
        "daca(mic(a,b))",
        "{",
        "  afiseaza(a);",
        "}",
        "altfel",
        "{",
        "  afiseaza(b);",
        "}"
    };

    int startY = y - CASETA_HEIGHT/3 + 10;
    for(int i=0;i<8;i++)
        outtextxy(x - textwidth(exempluCod[0])/2, startY + i*25, exempluCod[i]);
}

void drawTextSeven(int x, int y)
{
    settextstyle(INSTRUCTIUNI_FONT,0,3);
    char exempluCod[20][20] = {
        "cat timp(mare(a,b))",
        "{",
        "  dif(a,b);",
        "}"
    };

    int startY = y - CASETA_HEIGHT/5;
    for(int i=0;i<4;i++)
        outtextxy(x - textwidth(exempluCod[0])/2, startY + i*25, exempluCod[i]);
}

void drawTextEight(int x, int y)
{
    settextstyle(INSTRUCTIUNI_FONT,0,3);
    char exempluCod[20][25] = {
        "repeta",
        "{",
        "  dif(a,b);",
        "} cat timp(egal(a,b))"
    };

    int startY = y - CASETA_HEIGHT/5;
    for(int i=0;i<4;i++)
        outtextxy(x - textwidth(exempluCod[3])/2, startY + i*25, exempluCod[i]);
}

void waitForBackClick()
{
    bool redirect = false;
    while(!redirect)
    {
        int x, y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(WINDOW_WIDTH/2 - BTN_WIDTH/2 <= x && x<= WINDOW_WIDTH/2 + BTN_WIDTH/2 && 900 <= y && y <= 900 + 100)
                redirect = true;
        }
    }
}

int startInstructiuni()
{

    readimagefile(PATH_BG_INSTRUCTIUNI, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    drawBackButton();

    drawCaseta(250, 200);
    drawTextOne(250, 200);

    drawCaseta(723, 200);
    drawTextTwo(723, 200);

    drawCaseta(1196, 200);
    drawTextThree(1196, 200);

    drawCaseta(1669, 200);
    drawTextFour(1669, 200);


    drawCaseta(250, 600);
    drawTextFive(250, 600);

    drawCaseta(723, 600);
    drawTextSix(723, 600);

    drawCaseta(1196, 600);
    drawTextSeven(1196, 600);

    drawCaseta(1669, 600);
    drawTextEight(1669, 600);

    waitForBackClick();

    // returneaza 0 pentru intoarcerea la meniul principal
    return 0;
}


#endif // INSTRUCTIUNI_GRAFICA_H_INCLUDED
