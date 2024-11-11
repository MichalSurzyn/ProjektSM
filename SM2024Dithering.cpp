#include "SM2024Variables.h"
#include "SM2024CoreFunctions.h"
#include "SM2024HelperFunctions.h"
#include "SM2024BitConversion.h"


void zaktualizujTabliceBayera4(){
    int zakres = 256;
    int rozmiar = 4;
    float podzial = zakres * 1.0 / (rozmiar*rozmiar);

    for (int y=0; y<rozmiar; y++){
        for (int x=0; x<rozmiar; x++){
            zaktualizawanaTablicaBayera4[y][x] = (tablicaBayera4[y][x]*podzial)-podzial/2;
        }
    }
}

void bayer4x4RGB(){
    int rozmiar = 4;
    zaktualizujTabliceBayera4();
    SDL_Color kolor;
    Uint8 czerwony;
    Uint8 zielony;
    Uint8 niebieski;
    Uint8 tablica;

    for (int y=0; y<wysokosc/2; y++){
        for (int x=szerokosc/2; x<szerokosc; x++){
            kolor = getPixel(x,y);

            tablica = zaktualizawanaTablicaBayera4[y % rozmiar][x % rozmiar];
            czerwony = (kolor.r > tablica) ? czerwony = 255 : czerwony = 0;
            zielony = (kolor.g > tablica) ? zielony = 255 : zielony = 0;
            niebieski = (kolor.b > tablica) ? niebieski = 255 : niebieski = 0;
            setPixel(x - szerokosc/2,y + wysokosc/2,czerwony,zielony,niebieski);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void bayer4x4BW(){
    int rozmiar = 4;
    zaktualizujTabliceBayera4();
    SDL_Color kolor;
    Uint8 szary;
    Uint8 piksel;
    Uint8 tablica;

    for (int y=0; y<wysokosc/2; y++){
        for (int x=szerokosc/2; x<szerokosc; x++){
            kolor = getPixel(x,y);
            szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            setPixel(x,y,szary,szary,szary);

            tablica = zaktualizawanaTablicaBayera4[y % rozmiar][x % rozmiar];
            if (szary > tablica) {
                piksel = 255;
            }else{
                piksel = 0;
            }
            setPixel(x - szerokosc/2,y + wysokosc/2,piksel,piksel,piksel);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void floydRGB(){
    Uint8 nowyCzerwony,nowyZielony,nowyNiebieski,kolor7bit;
    SDL_Color kolor, nowyKolor, tymczasowyKolor;
    int tymczasowyCzerwony, tymczasowyZielony, tymczasowyNiebieski;
    int przesuniecie =1;

    float bledyCzerwony[(szerokosc/2)+2][(wysokosc/2)+2];
    float bledyZielony[(szerokosc/2)+2][(wysokosc/2)+2];
    float bledyNiebieski[(szerokosc/2)+2][(wysokosc/2)+2];
    memset(bledyCzerwony,0,sizeof(bledyCzerwony));
    memset(bledyZielony,0,sizeof(bledyZielony));
    memset(bledyNiebieski,0,sizeof(bledyNiebieski));
    int bladCzerwony=0;
    int bladZielony=0;
    int bladNiebieski=0;
    for(int y=0;y<wysokosc/2;y++){
        for(int x=0; x<szerokosc/2;x++){
            kolor = getPixel(x + szerokosc/2,y);
            tymczasowyCzerwony=kolor.r+bledyCzerwony[x+przesuniecie][y];
            tymczasowyZielony=kolor.g+bledyZielony[x+przesuniecie][y];
            tymczasowyNiebieski=kolor.b+bledyNiebieski[x+przesuniecie][y];

            tymczasowyCzerwony=normalizacja(tymczasowyCzerwony,0,255);
            tymczasowyZielony=normalizacja(tymczasowyZielony,0,255);
            tymczasowyNiebieski=normalizacja(tymczasowyNiebieski,0,255);

            tymczasowyKolor.r=tymczasowyCzerwony;
            tymczasowyKolor.g=tymczasowyZielony;
            tymczasowyKolor.b=tymczasowyNiebieski;

            kolor7bit = z24RGBna7RGB(tymczasowyKolor);
            nowyKolor = z7RGBna24RGB(kolor7bit);
            nowyCzerwony=nowyKolor.r;
            nowyZielony=nowyKolor.g;
            nowyNiebieski=nowyKolor.b;
            bladCzerwony=tymczasowyCzerwony-nowyCzerwony;
            bladZielony=tymczasowyZielony-nowyZielony;
            bladNiebieski=tymczasowyNiebieski-nowyNiebieski;

            setPixel(x ,y + wysokosc/2,nowyKolor.r,nowyKolor.g,nowyKolor.b);
            bledyCzerwony[x+1+przesuniecie][y ]+=(bladCzerwony*7.0/16.0);
            bledyCzerwony[x  +przesuniecie][y+1]+=(bladCzerwony*3.0/16.0);
            bledyCzerwony[x-1+przesuniecie][y+1]+=(bladCzerwony*5.0/16.0);
            bledyCzerwony[x+1+przesuniecie][y+1]+=(bladCzerwony*1.0/16.0);

            bledyZielony[x+1+przesuniecie][y ]+=(bladZielony*7.0/16.0);
            bledyZielony[x  +przesuniecie][y+1]+=(bladZielony*3.0/16.0);
            bledyZielony[x-1+przesuniecie][y+1]+=(bladZielony*5.0/16.0);
            bledyZielony[x+1+przesuniecie][y+1]+=(bladZielony*1.0/16.0);

            bledyNiebieski[x+1+przesuniecie][y ]+=(bladNiebieski*7.0/16.0);
            bledyNiebieski[x  +przesuniecie][y+1]+=(bladNiebieski*3.0/16.0);
            bledyNiebieski[x-1+przesuniecie][y+1]+=(bladNiebieski*5.0/16.0);
            bledyNiebieski[x+1+przesuniecie][y+1]+=(bladNiebieski*1.0/16.0);

        }
    }
    SDL_UpdateWindowSurface(window);
}

void floydBW(){
    Uint8 szary, nowySzary,szary7bit;
    SDL_Color kolor, nowyKolor, tymczasowyKolor;
    int tymczasowySzary;
    int przesuniecie = 1;

    float bledy[(szerokosc/2)+2][(wysokosc/2)+2];
    memset(bledy,0,sizeof(bledy));
    int blad=0;
    for(int y=0;y<wysokosc/2;y++){
        for(int x=0; x<szerokosc/2;x++){
            kolor = getPixel(x + szerokosc/2, y);
            szary=0.299*kolor.r+0.587*kolor.g+0.114*kolor.b;
            tymczasowySzary=szary+bledy[x+przesuniecie][y];

            tymczasowySzary=normalizacja(tymczasowySzary,0,255);

            tymczasowyKolor.r=tymczasowySzary;
            tymczasowyKolor.g=tymczasowySzary;
            tymczasowyKolor.b=tymczasowySzary;

            szary7bit = z24RGBna7BW(tymczasowyKolor);
            nowyKolor = z7BWna24RGB(szary7bit);
            nowySzary=nowyKolor.r;
            blad=tymczasowySzary-nowySzary;

            setPixel(x,y+wysokosc/2,nowyKolor.r,nowyKolor.g,nowyKolor.b);
            bledy[x+1+przesuniecie][y  ]+=(blad*7.0/16.0);
            bledy[x  +przesuniecie][y+1]+=(blad*3.0/16.0);
            bledy[x-1+przesuniecie][y+1]+=(blad*5.0/16.0);
            bledy[x+1+przesuniecie][y+1]+=(blad*1.0/16.0);

               }
    }

    SDL_UpdateWindowSurface(window);
}

void setDitheredRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b) {

    int threshold = tablicaBayera4[xx % 2][yy % 2]; // Pobranie progu z tablicy
    Uint8 r5 = (r >> 3) + threshold;       // Zastosowanie progu
    Uint8 g5 = (g >> 3) + threshold;
    Uint8 b5 = (b >> 3) + threshold;

    r5 = r5 > 31 ? 31 : r5; // Ograniczenie do zakresu 5-bitowego
    g5 = g5 > 31 ? 31 : g5;
    b5 = b5 > 31 ? 31 : b5;

    // Kodowanie w RGB555
    Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;

    // Przekonwertowanie na 24-bitowe kolory
    Uint8 r24 = r5 << 3;
    Uint8 g24 = g5 << 3;
    Uint8 b24 = b5 << 3;

    // Ustawienie piksela
    setPixel(xx, yy, r24, g24, b24);
}

void applyBayerDithering(int screenWidth, int screenHeight) {
    // Okreœlamy obszar lewego górnego rogu (zak³adamy po³owê szerokoœci i pe³n¹ wysokoœæ)
    int leftWidth = screenWidth / 2;
    int imageHeight = screenHeight / 2;
    SDL_Color pixel;
    // Iteracja po pikselach obrazu z lewego górnego rogu
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < leftWidth; x++) {
            // Pobranie piksela z lewego górnego rogu
            Uint8 r, g, b;
            pixel = getPixel(x, y);
             r = pixel.r;
             g = pixel.g;
             b = pixel.b;
            // Ustawienie pikseli w prawym górnym rogu (przesuniêcie o szerokoœæ / 2)
            setDitheredRGB555(x + leftWidth, y, r, g, b);
        }
    }
}
