#ifndef STRUCTURI_BLOCURI_DESENARE_H_INCLUDED
#define STRUCTURI_BLOCURI_DESENARE_H_INCLUDED

#include <iostream>
using namespace std;

const int LUNGIME_CONTINUT=100;

struct punct
{
    int x,y;
};

struct BlocSimplu
{
    char continut[LUNGIME_CONTINUT];
    punct centru;
    int lungime,latime;

};

struct BlocDaca
{
    BlocSimplu chenar;
    punct pozConditie;
    punct separare;
};

struct BlocPentru
{
    //BlocSimplu actiune;
    punct centruChenar;
    int lungimeChenar,latimeChenar;
    char conditie[LUNGIME_CONTINUT];

};

struct BlocCatTimp
{

    //BlocSimplu actiune;
    punct centruChenar;
    int lungimeChenar,latimeChenar;
    char conditie[LUNGIME_CONTINUT];
};

struct BlocRepeta
{
    //BlocSimplu actiune;
    punct centruChenar;
    int lungimeChenar,latimeChenar;
    char conditie[LUNGIME_CONTINUT];
};

struct BlocIntrerupe
{
    BlocSimplu chenar;
    punct separare;
    punct plecareSeparare;
};

struct BlocSelectieCaz
{
    int nrCazuri;
    int lungimeChenar;
    int latimeChenar;
    punct centruChenar;
    char conditie[LUNGIME_CONTINUT];
};


#endif // STRUCTURI_BLOCURI_DESENARE_H_INCLUDED
