#include "SM2024Undersampling.h"
#include "SM2024Variables.h"
#include "SM2024CoreFunctions.h"


void calculateSubFilter(){

    SDL_Color getColor;
    SDL_Color myColor;
    int counter = 0;
    uint8_t r,g,b;

    //getColor = getPixel(1,0);

    //subPaleta[0] = getColor;

    for(int x = 0; x < szerokosc/2; x++){
        for(int y = 0; y < wysokosc/2; y++){
            getColor = getPixel(x,y);
            myColor.r = getColor.r - subPaleta[counter-1].r;
            myColor.g = getColor.g - subPaleta[counter-1].g;
            myColor.b = getColor.b - subPaleta[counter-1].b;
            //cout << "r: " << (int)myColor.r << " g: " << (int)myColor.g << " b: " << (int)myColor.b << endl;
            subPaleta[counter] = myColor;

            counter++;
        }
    }

    counter = 0;
    //setPixel(1,0,subPaleta[0].r,subPaleta[0].g,subPaleta[0].b);
    for(int x = 0; x < szerokosc/2; x++){
        for(int y = 0; y < wysokosc/2; y++){
            r = subPaleta[counter-1].r + subPaleta[counter].r;
            g = subPaleta[counter-1].g + subPaleta[counter].g;
            b = subPaleta[counter-1].b + subPaleta[counter].b;
            setPixel(x + szerokosc/2,y,r,g,b);
            counter++;
        }
    }

}
