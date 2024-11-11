#ifndef SM2024HELPERFUNCTIONS_H_INCLUDED
#define SM2024HELPERFUNCTIONS_H_INCLUDED

#include <SDL2/SDL.h>


int normalizacja(int wartosc, int minimum, int maximum);

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);

Uint8 shiftByte(Uint8 b, Uint8 shiftAmount);

float calculateSaturation(float minimum, float maximum, float luminance);

float calculateHue(float r, float g, float b, float minimum, float maximum);

int calculateHSLtoRGBMethod(float x);

#endif // SM2024HELPERFUNCTIONS_H_INCLUDED
