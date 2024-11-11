#ifndef SM2024MEDIANCUT_H_INCLUDED
#define SM2024MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>


void medianCutBW(int start,int koniec, int iteracja);

void medianCut(int start,int koniec, int iteracja);

void sortujKubelekBW(int start ,int koniec, SDL_Color* targetPicture);

void sortujKubelekKolor(int start, int koniec, Uint8 sortowanie, SDL_Color* targetPicture);

int znajdzSasiadaBW(Uint8 wartosc);

int znajdzSasiada(SDL_Color kolor, SDL_Color* colorPalette);

#endif // SM2024MEDIANCUT_H_INCLUDED
