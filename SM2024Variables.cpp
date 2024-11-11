#include "SM2024Variables.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

char identyfikator[] = "MKJ";
SDL_Color paleta7DoPliku[128];
int counter = 0;

Uint8 paleta7DoPlikuUint8[szerokosc/2*wysokosc/2];
Uint16 szerokoscObrazka = szerokosc;
Uint16 wysokoscObrazka = wysokosc;

Uint8 tryb = 0;
Uint8 dithering = 3;
Uint8 rozmiarPalety = 0;

SDL_Color paleta7[320*200];
SDL_Color subPaleta[(szerokosc/2) * (wysokosc/2)];
int ileKolorow = 0;

SDL_Color obrazek[(szerokosc/2)*(wysokosc/2)];
SDL_Color obrazekTMP[256];

int ileKubelkow = 0;
SDL_Color paleta[128];

int tablicaBayera4[4][4] = { {6, 14, 8, 16},
    {10, 2, 12, 4},
    {7, 15, 5, 13},
    {11, 3, 9, 1}
};

float zaktualizawanaTablicaBayera4[4][4];
