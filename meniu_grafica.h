#ifndef MENIU_GRAFICA_H_INCLUDED
#define MENIU_GRAFICA_H_INCLUDED

#include<windows.h>

const char PATH_BG_MENU[] = "bg_menu.jpg";

const int WIDTH_BTN = 800;
const int HEIGHT_BTN = 100;
const int BTN_COLOR = COLORS.BLUE;
const int BTN_COLOR_HOVER = COLORS.GREEN;
const int NUMBER_OF_BUTTONS = 4;
char BTN_TEXT[NUMBER_OF_BUTTONS][30] = {
    "DIAGRAMA SIMPLA",
    "DIAGRAMA CU EXECUTIE",
    "INSTRUCTIUNI",
    "IESIRE"
};

struct buttonsCoords {
    int leftX, rightX;
    int upperY, lowerY;
    int centerX, centerY;
};

void calculateBtnCoords(buttonsCoords btnCoords[], int x, int y)
{
    for(int i=0;i<NUMBER_OF_BUTTONS;i++)
    {
        btnCoords[i].leftX = x - WIDTH_BTN/2;
        btnCoords[i].rightX = x + WIDTH_BTN/2;
        btnCoords[i].upperY = y - HEIGHT_BTN/2;
        btnCoords[i].lowerY = y + HEIGHT_BTN/2;
        btnCoords[i].centerX = x;
        btnCoords[i].centerY = y;
        y += 150;
    }
}

void drawButton(char text[], int btnNumber, buttonsCoords btnCoords[], int color)
{
    setbkcolor(color);
    setfillstyle(EMPTY_FILL, 0);
    bar3d(
              btnCoords[btnNumber].leftX,
              btnCoords[btnNumber].upperY,
              btnCoords[btnNumber].rightX,
              btnCoords[btnNumber].lowerY,
              20,
              1
          );

    setfillstyle(EMPTY_FILL, 0);
    floodfill(
                  (btnCoords[btnNumber].leftX + btnCoords[btnNumber].rightX)/2,
                  btnCoords[btnNumber].upperY - 2,
                  COLORS.WHITE
              );


    floodfill(
                  btnCoords[btnNumber].rightX + 2,
                  btnCoords[btnNumber].upperY,
                  COLORS.WHITE
              );

    settextstyle(DEFAULT_FONT,HORIZ_DIR, 4);
    outtextxy(
                  btnCoords[btnNumber].centerX - textwidth(text)/2,
                  btnCoords[btnNumber].centerY - textheight(text)/2,
                  text
              );

}

void isOnButton(int x, int y, buttonsCoords btnCoords[], int &lastHoveredBtn, int action, int &redirect)
{
    int activeHoveredBtn = -1;
    if(btnCoords[0].leftX <= x && x<= btnCoords[0].rightX)
    {
        for(int i=0;i<NUMBER_OF_BUTTONS;i++)
            if(btnCoords[i].upperY <= y && y <= btnCoords[i].lowerY)
                {
                    activeHoveredBtn = i;
                    if(action == WM_LBUTTONDOWN) redirect = i + 1;
                }

    }

    if(activeHoveredBtn != -1)
    {
        if(lastHoveredBtn != activeHoveredBtn)
            drawButton(BTN_TEXT[activeHoveredBtn], activeHoveredBtn, btnCoords, BTN_COLOR_HOVER);
        if(lastHoveredBtn != -1 && lastHoveredBtn != activeHoveredBtn)
            drawButton(BTN_TEXT[lastHoveredBtn], lastHoveredBtn, btnCoords, BTN_COLOR);
        lastHoveredBtn = activeHoveredBtn;
    }
    else if(lastHoveredBtn != -1)
    {
            drawButton(BTN_TEXT[lastHoveredBtn], lastHoveredBtn, btnCoords, BTN_COLOR);
            lastHoveredBtn = -1;
    }
}

int waitForClickEvent(buttonsCoords btnCoords[])
{
    int redirect = -1;
    int lastHoveredBtn = -1;
    while(redirect == -1)
    {
        int x, y;
        if(ismouseclick(WM_MOUSEMOVE))
        {
            getmouseclick(WM_MOUSEMOVE, x, y);
            isOnButton(x,y,btnCoords,lastHoveredBtn, WM_MOUSEMOVE, redirect);
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            isOnButton(x,y,btnCoords,lastHoveredBtn, WM_LBUTTONDOWN, redirect);
        }
    }
    return redirect;
}

int startMenu()
{

    readimagefile(PATH_BG_MENU, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    buttonsCoords btnCoords[4];
    calculateBtnCoords(btnCoords,WINDOW_WIDTH/2,440);

    for(int i=0;i<NUMBER_OF_BUTTONS;i++)
        drawButton(BTN_TEXT[i], i, btnCoords, BTN_COLOR);

    return waitForClickEvent(btnCoords);
}




#endif // MENIU_GRAFICA_H_INCLUDED
