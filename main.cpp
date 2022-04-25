#include <iostream>
#include <fstream>
#include <winbgim.h>
#include <cstring>
#include <graphics.h>
#include "utilitati.h"
#include "structuri_blocuri_desenare.h"
#include "variabile_grafica.h"
#include "functii_desenare.h"
#include "verificare_cod.h"
#include "parcurgere_pseudocod.h"
#include "instructiuni_grafica.h"
#include "meniu_grafica.h"
#include "redirect_app.h"

using namespace std;

int main()
{
    initwindow(WINDOW_WIDTH,WINDOW_HEIGHT);

    redictApp_StartPointFunction();

    closegraph();

    return 0;
}
