#ifndef SM2024COLORPALETTE_H_INCLUDED
#define SM2024COLORPALETTE_H_INCLUDED

#include <SDL2/SDL.h>

int dodajKolor(SDL_Color kolor);

int sprawdzKolor(SDL_Color kolor);

void czyscPalete();

Uint8 najwiekszaRoznica(int start, int koniec, SDL_Color* targetPicture);

void narysujPalete(SDL_Color* targetPalette);

#endif // SM2024COLORPALETTE_H_INCLUDED
