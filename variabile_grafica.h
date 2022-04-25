#ifndef VARIABILE_GRAFICA_H_INCLUDED
#define VARIABILE_GRAFICA_H_INCLUDED
const int WINDOW_HEIGHT=1080;
const int WINDOW_WIDTH=1920;
const int CENTRE_X=960;
const int CENTRE_Y=540;
const int LUNGIME=200;
const int DACA_LATIME=100;
const int ACTIUNE_LATIME=50;
const int BREAK_LATIME=50;
const int CAT_TIMP_LATIME=50;
const int PENTRU_LATIME=50;
const int REPETA_LATIME=50;
const int SELECTIE_LATIME=100;
const int BUFFER_SIZE = 255;

struct Dimensiuni
{
    int centruX=960;
    int centruY=540;
    int lungime=200;
    int dacaLatime=100;
    int actiuneLatime=50;
    int breakLatime=50;
    int catTimpLatime=50;
    int pentruLatime=50;
    int repetaLatime=50;
    int selectieLatime=100;
}DIMENSIUNE;

struct COLORS_STRUCT {
    int BLACK=0;
    int BLUE=1;
    int GREEN=2;
    int CYAN=3;
    int RED=4;
    int MAGENTA=5;
    int BROWN=6;
    int LIGHTGRAY=7;
    int DARKGRAY=8;
    int LIGHTBLUE=9;
    int LIGHTGREEN=10;
    int LIGHTCYAN=11;
    int LIGHTRED=12;
    int LIGHTMAGENTA=13;
    int YELLOW=14;
    int WHITE=15;
} COLORS;
#endif // VARIABILE_GRAFICA_H_INCLUDED
