#ifndef SM2024COREFUNCTIONS_H_INCLUDED
#define SM2024COREFUNCTIONS_H_INCLUDED

#include <SDL2/SDL.h>

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

SDL_Color getPixel(int x, int y);

void setPixelSurface(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B);

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface);

void ladujBMP(char const* nazwa, int x, int y);

void zapiszBMP(char const *nazwa, int startPixelX, int startPixelY);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

#endif // SM2024COREFUNCTIONS_H_INCLUDED
