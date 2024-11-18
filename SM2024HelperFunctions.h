#ifndef SM2024HELPERFUNCTIONS_H_INCLUDED
#define SM2024HELPERFUNCTIONS_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>


int normalizacja(int wartosc, int minimum, int maximum);

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);

Uint8 shiftByte(Uint8 b, Uint8 shiftAmount);

float calculateSaturation(float minimum, float maximum, float luminance);

float calculateHue(float r, float g, float b, float minimum, float maximum);

int calculateHSLtoRGBMethod(float x);

void ByteRunKompresja(const uint8_t wejscie[], int dlugosc, const char* nazwaPlikuWyjsciowego);

int rozmiarPliku(const char* nazwaPliku);

std::vector<uint8_t> ByteRunDekompresja(const char* nazwaPlikuWejsciowego);

void rysujObraz(const std::vector<uint8_t>& dane);

#endif // SM2024HELPERFUNCTIONS_H_INCLUDED
