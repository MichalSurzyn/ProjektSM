#ifndef SM2024BITCONVERSION_H_INCLUDED
#define SM2024BITCONVERSION_H_INCLUDED

#include <SDL2/SDL.h>

Uint8 z24RGBna7RGB(SDL_Color kolor);

SDL_Color z7RGBna24RGB(Uint8 kolor7bit);

Uint8 z24RGBna7BW(SDL_Color kolor);

SDL_Color z7BWna24RGB(Uint8 szary7bit);

void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);

void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);

SDL_Color getRGB555(int xx, int yy);

Uint16 getRGB555_(int xx, int yy);

SDL_Color getRGB565(int xx, int yy);

Uint16 getRGB565_(int xx, int yy);

#endif // SM2024BITCONVERSION_H_INCLUDED
