#include <iostream>
#include <utility>

#include "SM2024MedianCut.h"
#include "SM2024Variables.h"
#include "SM2024ColorPalette.h"

using namespace std;


void medianCutBW(int start,int koniec, int iteracja){
    if(iteracja>0){
        sortujKubelekBW(start, koniec, obrazek);

        int srodek=(start+koniec+1)/2;
        medianCutBW(start,srodek-1,iteracja-1);
        medianCutBW(srodek,koniec,iteracja-1);
    }
    else{
        int sumaBW=0;
        for(int p=start;p<=koniec;p++){
            sumaBW += obrazek[p].r;
        }
        Uint8 noweBW = sumaBW /(koniec+1-start);
        SDL_Color nowyKolor={noweBW,noweBW,noweBW};
        paleta[ileKubelkow]=nowyKolor;
        ileKubelkow++;
    }
}

void medianCut(int start,int koniec, int iteracja){
    int czesc = 1;
    if(iteracja>0){
        Uint8 sortowanie = najwiekszaRoznica(start, koniec, obrazek);
        sortujKubelekKolor(start, koniec, sortowanie, obrazek);

        int srodek=(start+koniec+1)/2;
        medianCut(start,srodek-1,iteracja-1);
        medianCut(srodek,koniec,iteracja-1);
    }
    else{
        int sumaR=0, sumaG=0, sumaB=0;
        for(int i=start;i<=koniec;i++){
            sumaR+=obrazek[i].r;
            sumaG+=obrazek[i].g;
            sumaB+=obrazek[i].b;
        }
        SDL_Color nowyKolor{sumaR/(koniec+1-start), sumaG/(koniec+1-start), sumaB/(koniec+1-start)};
        paleta[ileKubelkow]=nowyKolor;
        ileKubelkow++;
    }
}

void sortujKubelekBW(int start ,int koniec, SDL_Color* targetPicture){
    for(int i = start+1;i < koniec; i++) {
        int j = i;
        while(j > start && targetPicture[j].r < targetPicture[j-1].r) {
            swap(targetPicture[j], targetPicture[j-1]);
            j--;
        }
    }
}

void sortujKubelekKolor(int start, int koniec, Uint8 sortowanie, SDL_Color* targetPicture){
    switch(sortowanie){
        case 1:
            for(int i = start+1;i < koniec; i++) {
                int j = i;
                while(j > start && targetPicture[j].r < targetPicture[j-1].r) {
                    swap(targetPicture[j], targetPicture[j-1]);
                    j--;
                }
            }
            break;
        case 2:
            for(int i = start+1;i < koniec; i++) {
                int j = i;
                while(j > start && targetPicture[j].g < targetPicture[j-1].g) {
                    swap(targetPicture[j], targetPicture[j-1]);
                    j--;
                }
            }
            break;
        case 3:
            for(int i = start+1;i < koniec; i++) {
                int j = i;
                while(j > start && targetPicture[j].b < targetPicture[j-1].b) {
                    swap(targetPicture[j], targetPicture[j-1]);
                    j--;
                }
            }
            break;
    }
}

int znajdzSasiadaBW(Uint8 wartosc){
    int minimum = 999;
    int indexMinimum=0;
    int odleglosc=0;
    for(int i=0;i<128;i++){
        odleglosc=abs(wartosc-paleta[i].r);
        if(odleglosc<minimum){
            minimum=odleglosc;
            indexMinimum=i;
        }
    }
    return indexMinimum;
}

int znajdzSasiada(SDL_Color kolor, SDL_Color* colorPalette){
    int minimum = 999;
    int indexMinimum=0;
    int odleglosc=0;
    for(int i=0;i<128;i++){
        odleglosc = abs(kolor.r - colorPalette[i].r) + abs(kolor.g - colorPalette[i].g) + abs(kolor.b - colorPalette[i].b);
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}
