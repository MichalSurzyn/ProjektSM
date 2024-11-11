#include <math.h>

#include "SM2024BitConversion.h"
#include "SM2024CoreFunctions.h"

Uint8 z24RGBna7RGB(SDL_Color kolor){

    Uint8 R,G,B,kolor7bit;
    int nowyR, nowyG, nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    nowyR=round(R*3.0/255.0);
    nowyG=round(G*7.0/255.0);
    nowyB=round(B*3.0/255.0);

    kolor7bit = (nowyR<<6) | (nowyG<<3) | (nowyB<<1);

    return kolor7bit;
}

SDL_Color z7RGBna24RGB(Uint8 kolor7bit){
    //RRGGGBB0
    int R,G,B,nowyR,nowyG,nowyB;
    SDL_Color kolor24RGB;
    nowyR = (kolor7bit & (0b11000000)) >> 6;
    nowyG = (kolor7bit & (0b00111000)) >> 3;
    nowyB = (kolor7bit & (0b00000110)) >> 1;


    R= nowyR*255.0/3.0;
    G= nowyG*255.0/7.0;
    B= nowyB*255.0/3.0;

    kolor24RGB.r = R;
    kolor24RGB.g = G;
    kolor24RGB.b = B;

    return kolor24RGB;
}

Uint8 z24RGBna7BW(SDL_Color kolor){

    Uint8 szary8bit, szary7bit;

    szary8bit = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;

    szary7bit = round(szary8bit*127.0/255.0);

    return szary7bit;
}

SDL_Color z7BWna24RGB(Uint8 szary7bit){

    SDL_Color kolor;
    Uint8 szary8bit;
    szary8bit = round(szary7bit*255.0/127.0);
    kolor = {szary8bit, szary8bit, szary8bit};


    return kolor;
};

void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b){
// 00000|000
Uint8 r5 = r >> 3;
Uint8 g5 = g >> 3;
Uint8 b5 = b >> 3;

// 0000 0000 0000 0000

//do 15bit
Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;

// 0000 0000 0000 0000 0000 0000

//do 24bit 8 8 8
Uint8 r24 = r5 << 3;
Uint8 g24 = g5 << 3;
Uint8 b24 = b5 << 3;

setPixel(xx, yy, r24, g24, b24);

}

void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b){
// 00000000
Uint8 r5 = r >> 3;
Uint8 g6 = g >> 2;
Uint8 b5 = b >> 3;

// 00000 000000 00000

//do 15bit
Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;

// 0000 0000 0000 0000 0000 0000

//do 24bit 8 8 8
Uint8 r24 = r5 << 3;
Uint8 g24 = g6 << 2;
Uint8 b24 = b5 << 3;

setPixel(xx, yy, r24, g24, b24);

}

SDL_Color getRGB555(int xx, int yy) {

    SDL_Color color = getPixel(xx, yy);

    //8na b5bit
    Uint8 r5 = color.r >> 3;
    Uint8 g5 = color.g >> 3;
    Uint8 b5 = color.b >> 3;

    Uint8 r = r5 << 3;
    Uint8 g = g5 << 3;
    Uint8 b = b5 << 3;

    SDL_Color resultColor = {r, g, b, 255};
    return resultColor;
}

Uint16 getRGB555_(int xx, int yy) {

    SDL_Color color = getPixel(xx, yy);

    //8bit na 5bit
    Uint16 r5 = (color.r >> 3) << 10;
    Uint16 g5 = (color.g >> 3) << 5;
    Uint16 b5 = color.b >> 3;
    Uint16 rgb555 = r5 | g5 | b5;

    return rgb555;
}

SDL_Color getRGB565(int xx, int yy) {

    SDL_Color color = getPixel(xx, yy);

    Uint8 r5 = color.r >> 3;
    Uint8 g6 = color.g >> 2;
    Uint8 b5 = color.b >> 3;

    Uint8 r = r5 << 3;
    Uint8 g = g6 << 2;
    Uint8 b = b5 << 3;

    SDL_Color resultColor = {r, g, b, 255};
    return resultColor;
}

Uint16 getRGB565_(int xx, int yy) {

    SDL_Color color = getPixel(xx, yy);

    Uint16 r5 = (color.r >> 3) << 11;
    Uint16 g6 = (color.g >> 2) << 5;
    Uint16 b5 = color.b >> 3;
    Uint16 rgb565 = r5 | g6 | b5;

    return rgb565;
}
