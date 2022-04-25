#ifndef COMPILARE_PSEUDOCOD_H_INCLUDED
#define COMPILARE_PSEUDOCOD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Variabile {
    struct {
        char identificator[15];
        int valoare = 0;
    } lista[20];
    int lungime = 0;
};

struct RaspunsCompilare {
    char mesaj[400]="";
    bool eroare = false;
};

int pozitieVariabila(Variabile variabile, char var[])
{
    for(int i=0;i<variabile.lungime;i++)
            if(!strcmp(variabile.lista[i].identificator, var))
                return i;
    return -1;
}

//  egal(a,5);

int valRec(char text[], Variabile variabile, RaspunsCompilare &raspComp)
{
    if(isNumber(text)) return atoi(text);
    else if(isSintaticVar(text))
    {
         int pozVar = pozitieVariabila(variabile, text);
         if(pozVar == -1)
         {
             raspComp.eroare = true;
             strcat(raspComp.mesaj,"Variabila ");
             strcat(raspComp.mesaj,text);
             strcat(raspComp.mesaj," nu a fost initializata.\0");
             return 0;
         }
         return variabile.lista[pozVar].valoare;
    }
    char auxText[250];
    strcpy(auxText, text);
    extragereConditie(text);
    trim(text);
    if(incepeCu(auxText, "neg")) return !valRec(text, variabile, raspComp);

    char argUnu[100], argDoi[100];
    refArgumente(argUnu, argDoi, text);

    if(incepeCu(auxText, "egal")) return (valRec(argUnu, variabile, raspComp) == valRec(argDoi, variabile, raspComp));
    else if(incepeCu(auxText, "inegal")) return (valRec(argUnu,variabile, raspComp) != valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "mareg")) return (valRec(argUnu,variabile, raspComp) >= valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "micg")) return (valRec(argUnu,variabile, raspComp) <= valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "mare")) return (valRec(argUnu,variabile, raspComp) > valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "mic")) return (valRec(argUnu,variabile, raspComp) < valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "si")) return (valRec(argUnu,variabile, raspComp) && valRec(argDoi,variabile, raspComp));
    else if(incepeCu(auxText, "sau")) return (valRec(argUnu,variabile, raspComp) || valRec(argDoi,variabile, raspComp));

    return 0;
}

void initPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char *var = strtok(primitiva, ",");
    while(var != NULL)
    {
        trim(var);
        if(pozitieVariabila(variabile, var) != -1)
        {
            raspComp.eroare = true;
            strcat(raspComp.mesaj,"Identificatorul ");
            strcat(raspComp.mesaj,var);
            strcat(raspComp.mesaj," apare de mai multe ori!\0");
        }
        strcpy(variabile.lista[variabile.lungime++].identificator, var);
        var = strtok(NULL , ",");
    }
}

void afisarePrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char parametrii[100][100];
    int nr_parametrii;
    strtok_custom(parametrii, primitiva, nr_parametrii);

    for(int i=0;i<=nr_parametrii;i++)
    {
        trim(parametrii[i]);
        if(!strcmp(parametrii[i], "LN")) strcat(raspComp.mesaj, "\n");
        else if(parametrii[i][0] == '"' && parametrii[i][strlen(parametrii[i])-1] == '"')
        {
            strcat(raspComp.mesaj, parametrii[i]);
            strcat(raspComp.mesaj, " ");
        }
        else {
            char numberToArray[10];
            itoa(valRec(parametrii[i],variabile, raspComp),numberToArray,10);
            strcat(raspComp.mesaj, numberToArray);
            strcat(raspComp.mesaj, " ");
        }
    }
}

void mutaPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
         raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare = valRec(argDoi,variabile, raspComp);
}

void sumPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
         raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare += valRec(argDoi,variabile, raspComp);
}

void difPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare -= valRec(argDoi,variabile, raspComp);
}

void prodPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare *= valRec(argDoi,variabile, raspComp);
}

void impPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    int valoare_returnata = valRec(argDoi,variabile, raspComp);
    if(valoare_returnata == 0)
    {
         raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu poate fi impartita la 0.\0");
         return;
    }
    else variabile.lista[pozVar].valoare /=  valoare_returnata;
}

void modPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    int valoare_returnata = valRec(argDoi,variabile, raspComp);
    if(valoare_returnata == 0)
    {
         raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu poate fi impartita la 0.\0");
         return;
    }
    else variabile.lista[pozVar].valoare %=  valoare_returnata;
}

void expPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    char argUnu[30], argDoi[30];
    refArgumente(argUnu, argDoi, primitiva);
    int pozVar = pozitieVariabila(variabile, argUnu);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, argUnu);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare = pow(variabile.lista[pozVar].valoare, valRec(argDoi,variabile, raspComp));
}

void incrPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    int pozVar = pozitieVariabila(variabile, primitiva);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, primitiva);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare++;
}

void decrPrimitiva(char primitiva[], Variabile &variabile, RaspunsCompilare &raspComp)
{
    extragereConditie(primitiva);
    trim(primitiva);
    int pozVar = pozitieVariabila(variabile, primitiva);
    if(pozVar == -1)
    {
        raspComp.eroare = true;
         strcat(raspComp.mesaj,"Variabila ");
         strcat(raspComp.mesaj, primitiva);
         strcat(raspComp.mesaj," nu a fost initializata.\0");
         return;
    }
    variabile.lista[pozVar].valoare--;
}

void parcurgereArboreCompilare(nod *arb, Variabile &variabile, RaspunsCompilare &raspComp)
{
    if(arb == NULL || raspComp.eroare) return;
    int caz_continuare = 0;
    char content[60];

    strcpy(content,arb->content);


    if(!strcmp(arb->typeOfBlock, "ACTION"))
    {
        if(incepeCu(content, "init")) initPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "muta")) mutaPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "afiseaza")) afisarePrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "incr")) incrPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "decr")) decrPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "sum")) sumPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "dif")) difPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "prod")) prodPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "imp")) impPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "exp")) expPrimitiva(content, variabile, raspComp);
        else if(incepeCu(content, "mod")) modPrimitiva(content, variabile, raspComp);
    }
    else if(!strcmp(arb->typeOfBlock, "IF"))
    {
        if(valRec(content, variabile, raspComp) == 0) caz_continuare = 1;
    }
    else if(!strcmp(arb->typeOfBlock, "WHILE"))
    {
        if(valRec(content, variabile, raspComp) != 0) caz_continuare = 2;
        else return;
    }
    else if(!strcmp(arb->typeOfBlock, "DO_WHILE")) caz_continuare = 3;


    if(caz_continuare == 0)
    {
        for(int i=0;i<arb->nrOfChildren;i++)
            if(strcmp(arb->children[i]->typeOfBlock, "ELSE") != 0)
                parcurgereArboreCompilare(arb->children[i], variabile, raspComp);
    }
    else if(caz_continuare == 1)
    {
        if(arb->nrOfChildren > 0 && strcmp(arb->children[arb->nrOfChildren-1]->typeOfBlock, "ELSE") == 0)
            parcurgereArboreCompilare(arb->children[arb->nrOfChildren-1], variabile, raspComp);
    }
    else if(caz_continuare == 2)
    {
        for(int i=0;i<arb->nrOfChildren;i++)
                parcurgereArboreCompilare(arb->children[i], variabile, raspComp);
        parcurgereArboreCompilare(arb, variabile, raspComp);
    }
    else if(caz_continuare == 3)
    {
        for(int i=0;i<arb->nrOfChildren;i++)
                parcurgereArboreCompilare(arb->children[i], variabile, raspComp);
        if(valRec(content, variabile, raspComp) == 0) return;
        parcurgereArboreCompilare(arb, variabile, raspComp);
    }

}

void startCompilare(nod *arb,RaspunsCompilare &raspComp)
{
    Variabile variabile;
    parcurgereArboreCompilare(arb, variabile, raspComp);
    trim(raspComp.mesaj);
}


#endif // COMPILARE_PSEUDOCOD_H_INCLUDED
