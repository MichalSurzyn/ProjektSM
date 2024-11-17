#include "SM2024Undersampling.h"
#include "SM2024Variables.h"
#include "SM2024CoreFunctions.h"
#include "SM2024ColorModels.h"

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

//4:2:0

void podprobkowanieYIQ(int dx, int dy){

    SDL_Color picked;
    YIQ transformed;
    YIQ cell[4];
    int half_width = szerokosc/2;

    for (int j = 0; j < wysokosc/2-1; j++){
        for (int i = 0; i < half_width-1; i++){

                cell[0] = getYIQ(i,j);
                cell[1] = getYIQ(i+1,j);
                cell[2] = getYIQ(i,j+1);
                cell[3] = getYIQ(i+1,j+1);
            float sharedI = 0;
            float sharedQ = 0;
            for (int c = 0; c < 4; c++){
                sharedI += cell[c].i;
                sharedQ += cell[c].q;
            }
            sharedI /= 4.0;
            sharedQ /= 4.0;

            for (int v = 0; v < 2; v++){
                for (int h = 0; h < 2; h++){
                    setYIQ(i+dx+h,j+dy+v, cell[h+v].y,sharedI,sharedQ);
                }
            }
            setYIQ(i+dx,j+dy, cell[0].y,sharedI,sharedQ);
            setYIQ(i+dx+1,j+dy, cell[1].y,sharedI,sharedQ);
            setYIQ(i+dx,j+dy+1, cell[2].y,sharedI,sharedQ);
            setYIQ(i+dx+1,j+dy+1, cell[3].y,sharedI,sharedQ);
        }
    }
}

void podprobkowanieYCbCr(int dx, int dy){
    SDL_Color picked;
    YCbCr transformed;
    YCbCr cell[4];
    int half_width = szerokosc/2;

    for (int i = 0; i < half_width-1; i++){
        for (int j = 0; j < wysokosc/2-1; j++){
                cell[0] = getYCbCr(i,j);
                cell[1] = getYCbCr(i+1,j);
                cell[2] = getYCbCr(i,j+1);
                cell[3] = getYCbCr(i+1,j+1);
            float sharedCb = 0;
            float sharedCr = 0;
            for (int c = 0; c < 4; c++){
                sharedCb += cell[c].cb;
                sharedCr += cell[c].cr;
            }
            sharedCb /= 4.0;
            sharedCr /= 4.0;

            setYCbCr(i+dx,j+dy, cell[0].y,sharedCb,sharedCr);
            setYCbCr(i+dx+1,j+dy, cell[1].y,sharedCb,sharedCr);
            setYCbCr(i+dx,j+dy+1, cell[2].y,sharedCb,sharedCr);
            setYCbCr(i+dx+1,j+dy+1, cell[3].y,sharedCb,sharedCr);
        }
    }
}

void podprobkowanieYUV(int dx, int dy){
    SDL_Color picked;
    YUV transformed;
    YUV cell[4];
    int half_width = szerokosc/2;

    for (int i = 0; i < half_width-1; i++){
        for (int j = 0; j < wysokosc/2-1; j++){

                cell[0] = getYUV(i,j);
                cell[1] = getYUV(i+1,j);
                cell[2] = getYUV(i,j+1);
                cell[3] = getYUV(i+1,j+1);
            float sharedU = 0;
            float sharedV = 0;
            for (int c = 0; c < 4; c++){
                sharedU += cell[c].u;
                sharedV += cell[c].v;
            }
            sharedU /= 4.0;
            sharedV /= 4.0;


            setYUV(i+dx,j+dy, cell[0].y,sharedU,sharedV);
            setYUV(i+dx+1,j+dy, cell[1].y,sharedU,sharedV);
            setYUV(i+dx,j+dy+1, cell[2].y,sharedU,sharedV);
            setYUV(i+dx+1,j+dy+1, cell[3].y,sharedU,sharedV);
        }
    }
}

void podprobkowanieHSL(int dx, int dy){
    HSL cell[4];
    int half_width = szerokosc / 2;

    for (int i = 0; i < half_width - 1; i++) {
        for (int j = 0; j < wysokosc / 2 - 1; j++) {
            // Pobierz wartości HSL dla 4 pikseli w bloku 2x2
            cell[0] = getHSL(i, j);
            cell[1] = getHSL(i + 1, j);
            cell[2] = getHSL(i, j + 1);
            cell[3] = getHSL(i + 1, j + 1);

            // Oblicz średnie wartości dla H i S
            float sharedH = 0, sharedS = 0;
            for (int c = 0; c < 4; c++) {
                sharedH += cell[c].h;
                sharedS += cell[c].s;
            }
            sharedH /= 4.0;
            sharedS /= 4.0;

            // Zachowaj oryginalną wartość L dla każdego piksela
            setHSL(i + dx, j + dy, sharedH, sharedS, cell[0].l);
            setHSL(i + dx + 1, j + dy, sharedH, sharedS, cell[1].l);
            setHSL(i + dx, j + dy + 1, sharedH, sharedS, cell[2].l);
            setHSL(i + dx + 1, j + dy + 1, sharedH, sharedS, cell[3].l);
        }
    }
}
