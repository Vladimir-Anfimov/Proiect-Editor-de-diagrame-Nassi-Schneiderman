#ifndef REDIRECT_APP_H_INCLUDED
#define REDIRECT_APP_H_INCLUDED

// 0 = meniu
// 1 = diagrama simpla
// 2 = diagrama cu executie
// 3 = instructiuni
// 4 = exit

const char MUSIC_MENU_PATH[] = "music_menu.wav";

void redictApp_StartPointFunction(int selectApp = 0)
{
    bool exitApp = false;

     PlaySound(MUSIC_MENU_PATH,NULL,SND_ASYNC);

    while(!exitApp)
    {
        if(selectApp == 0) selectApp = startMenu();
        else if(selectApp == 1) selectApp=startDesenareDiagramaSimpla();
        else if(selectApp == 2) selectApp=startDesenareDiagramaCuExecutie();
        else if(selectApp == 3) selectApp = startInstructiuni();
        else if(selectApp == 4) exitApp = true;
    }
}

#endif // REDIRECT_APP_H_INCLUDED
