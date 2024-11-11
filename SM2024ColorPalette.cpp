#include <iostream>

#include "SM2024ColorPalette.h"
#include "SM2024Variables.h"
#include "SM2024HelperFunctions.h"
#include "SM2024CoreFunctions.h"

using namespace std;

int dodajKolor(SDL_Color kolor){
    int aktualnyKolor = ileKolorow;
    if (aktualnyKolor < 128){
        paleta7[aktualnyKolor] = kolor;
    }

    ileKolorow++;
    return aktualnyKolor;
}

int sprawdzKolor(SDL_Color kolor){
    if(ileKolorow > 0){
        for(int k = 0; k < ileKolorow; k++){
            if(porownajKolory(kolor,paleta7[k]))
                return k;
        }
    }
    return dodajKolor(kolor);
}

void czyscPalete(){
    ileKolorow=0;
    for(int k=0; k<256;k++)
        paleta7[k]={0,0,0};
}

Uint8 najwiekszaRoznica(int start,int koniec, SDL_Color* targetPicture){
    int skladowa;
    int diffR, diffG, diffB;
    int minR = targetPicture[start].r;
    int minG = targetPicture[start].g;
    int minB = targetPicture[start].b;
    int maxR = targetPicture[start].r;
    int maxG = targetPicture[start].g;
    int maxB = targetPicture[start].b;
    for(int i = start+1; i<koniec; i++){
        if(targetPicture[i].r > maxR) maxR = targetPicture[i].r;
        if(targetPicture[i].g > maxG) maxG = targetPicture[i].g;
        if(targetPicture[i].b > maxB) maxB = targetPicture[i].b;
        if(targetPicture[i].r < minR) minR = targetPicture[i].r;
        if(targetPicture[i].g < minG) minG = targetPicture[i].g;
        if(targetPicture[i].b < minB) minB = targetPicture[i].b;
    }
    diffR = maxR - minR;
    diffG = maxG - minG;
    diffB = maxB - minB;
    if(diffR == max(diffR,max(diffB,diffG))) {skladowa = 1;}
    else if(diffG == max(diffR,max(diffB,diffG))) {skladowa = 2;}
    else if(diffB == max(diffR,max(diffB,diffG))) {skladowa = 3;}
    return skladowa;
}

void narysujPalete(SDL_Color* targetPalette ){
    int indeksKoloru = 0;
    int i, a, y, x;
    SDL_Color aktualnyKolor = targetPalette[indeksKoloru];

    for(i = 0; i < wysokosc/2; i += (wysokosc/2)/8){
        for(a = 0; a < szerokosc/2; a += (szerokosc/2)/16){
            for(y = i; y < i + (wysokosc/2)/8; y++){
                for(x = a; x < a + (szerokosc/2)/16; x++){
                    setPixel(x, y + wysokosc/2, aktualnyKolor.r, aktualnyKolor.g, aktualnyKolor.b);
                }
            }
            indeksKoloru++;
            aktualnyKolor = targetPalette[indeksKoloru];
        }
    }
}
