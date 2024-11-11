#include <iostream>
#include <math.h>

#include "SM2024ColorModels.h"
#include "SM2024CoreFunctions.h"
#include "SM2024HelperFunctions.h"

using namespace std;


YUV getYUV(int xx, int yy){

    YUV yuv;
    float y;
    float u;
    float v;
    int r;
    int g;
    int b;
    SDL_Color colorRGB;

    // przypisanie koloru wybranego piksela do zmiennej
    colorRGB = getPixel(xx, yy);

    // przypisanie poszczególnych barw do osobnych zmiennych
    r = colorRGB.r; g = colorRGB.g; b = colorRGB.b;

    // wyliczanie wartoœci y, u i v
    y = (0.299  * r) + (0.587  * g) + (0.114  * b);
    u = -(0.14713 * r) - (0.28886 * g) + (0.436 * b);
    v = (0.615 * r) - (0.51499 * g) - (0.10001 * b);

    // przypisanie wyliczonych wartoœci do struktury
    yuv.y = y;
    yuv.u = u;
    yuv.v = v;

    return yuv;
}

void setYUV (int xx, int yy, float y, float u, float v){

    int r;
    int g;
    int b;

    // konwersja modelu YUV na RGB
    r = y + (1.13983 * v);
    g = y - (0.39465 * u) - (0.58060 * v);
    b = y + (2.03211 * u);

    r = normalizacja(r, 0, 255);
    g = normalizacja(g, 0, 255);
    b = normalizacja(b, 0, 255);

    setPixel(xx, yy, r, g, b);

}

YIQ getYIQ(int xx, int yy){

    YIQ yiq;
    float y;
    float i;
    float q;
    int r;
    int g;
    int b;
    SDL_Color colorRGB;

    // przypisanie koloru wybranego piksela do zmiennej
    colorRGB = getPixel(xx, yy);

    // przypisanie poszczególnych barw do osobnych zmiennych
    r = colorRGB.r; g = colorRGB.g; b = colorRGB.b;

    // wyliczanie wartoœci y, i i q
    y = (0.299  * r) + (0.587  * g) + (0.114  * b);
    i = (0.5959 * r) - (0.2746 * g) - (0.3213 * b);
    q = (0.2115 * r) - (0.5227 * g) + (0.3112 * b);

    // przypisanie wyliczonych wartoœci do struktury
    yiq.y = y;
    yiq.i = i;
    yiq.q = q;

    return yiq;
}

void setYIQ (int xx, int yy, float y, float i, float q){

    int r;
    int g;
    int b;

    // konwersja modelu YIQ na RGB
    float wspI = 0.5 / 0.5959;
    float wspQ = 0.5 / 0.5227;
    r = y + (0.956 / wspI * (i - 128)) + (0.619 / wspQ * (q - 128));
    g = y - (0.272 / wspI * (i - 128)) - (0.647 / wspQ * (q - 128));
    b = y - (1.106 / wspI * (i - 128)) + (1.703 / wspQ * (q - 128));

    r = normalizacja(r, 0, 255);
    g = normalizacja(g, 0, 255);
    b = normalizacja(b, 0, 255);

    setPixel(xx, yy, r, g, b);

}

YCbCr getYCbCr(int xx, int yy){

    YCbCr ycbcr;
    float y;
    float cb;
    float cr;
    int r;
    int g;
    int b;
    SDL_Color colorRGB;

    // przypisanie koloru wybranego piksela do zmiennej
    colorRGB = getPixel(xx, yy);

    // przypisanie poszczególnych barw do osobnych zmiennych
    r = colorRGB.r; g = colorRGB.g; b = colorRGB.b;

    // wyliczanie wartoœci y, cb i cr
    y  = 0   + (0.299    * r) + (0.587    * g) + (0.114    * b);
    cb = 128 - (0.168736 * r) - (0.331264 * g) + (0.5      * b);
    cr = 128 + (0.5      * r) - (0.418688 * g) - (0.081312 * b);

    // przypisanie wyliczonych wartoœci do struktury
    ycbcr.y = y;
    ycbcr.cb = cb;
    ycbcr.cr = cr;

    return ycbcr;
}

void setYCbCr (int xx, int yy, float y, float cb, float cr){

    uint8_t r;
    uint8_t g;
    uint8_t b;

    // konwersja modelu YCbCr na RGB
    r = y + 1.402 * (cr - 128);
    g = y - (0.344136 * (cb - 128)) - (0.714136 * (cr - 128));
    b = y + 1.772 * (cb - 128);

    r = normalizacja(r, 0, 255);
    g = normalizacja(g, 0, 255);
    b = normalizacja(b, 0, 255);


    setPixel(xx, yy, r, g, b);

}

void setHSL(int xx, int yy, float h, float s, float l){

    float r, g, b, temp1, temp2, tempR, tempG, tempB, barwa;

    if(s == 0 && h == 0){
        r = 255 * l;
        g = 255 * l;
        b = 255 * l;
        setPixel(xx, yy, r, g, b);
        return;
    }

    if(l < 0.5) temp1 = l * (1.0 + s);
    if(l >= 0.5) temp1 = l + s - l * s;

    temp2 = 2 * l - temp1;

    barwa = h / 360.0;

    tempR = barwa + 0.333;
    if(tempR < 0) tempR += 1;
    if(tempR > 1) tempR -= 1;

    tempG = barwa;
    if(tempG < 0) tempG += 1;
    if(tempG > 1) tempG -= 1;

    tempB = barwa - 0.333;
    if(tempB < 0) tempB += 1;
    if(tempB > 1) tempB -= 1;

    switch(calculateHSLtoRGBMethod(tempR)){
        case 1:
            r = temp2 + (temp1 - temp2) * 6 * tempR;
            break;
        case 2:
            r = temp1;
            break;
        case 3:
            r = temp2 + (temp1 - temp2) * (0.666 - tempR) * 6;
            break;
        case 4:
            r = temp2;
            break;
        default:
            cout << "Bład podczas wybierania metody r\n";
    }

    switch(calculateHSLtoRGBMethod(tempG)){
        case 1:
            g = temp2 + (temp1 - temp2) * 6 * tempG;
            break;
        case 2:
            g = temp1;
            break;
        case 3:
            g = temp2 + (temp1 - temp2) * (0.666 - tempG) * 6;
            break;
        case 4:
            g = temp2;
            break;
        default:
            cout << "Bład podczas wybierania metody g\n";
    }

    switch(calculateHSLtoRGBMethod(tempB)){
        case 1:
            b = temp2 + (temp1 - temp2) * 6 * tempB;
            break;
        case 2:
            b = temp1;
            break;
        case 3:
            b = temp2 + (temp1 - temp2) * (0.666 - tempB) * 6;
            break;
        case 4:
            b = temp2;
            break;
        default:
            cout << "Bład podczas wybierania metody b\n";
    }

    r *= 255;
    g *= 255;
    b *= 255;

    int rInt = static_cast<int>(round(r));
    int gInt = static_cast<int>(round(g));
    int bInt = static_cast<int>(round(b));

    rInt = normalizacja(rInt, 0, 255);
    gInt = normalizacja(gInt, 0, 255);
    bInt = normalizacja(bInt, 0, 255);

    setPixel(xx, yy, rInt, gInt, bInt);
    return;
}

HSL getHSL(int xx, int yy){

    SDL_Color pixelColor;
    HSL hsl;
    float r, g, b, minColor, maxColor;

    pixelColor = getPixel(xx, yy);

    // konwersja wartości RGB z zakresu 0-255 na zakres 0-1
    r = pixelColor.r / 255.0;
    g = pixelColor.g / 255.0;
    b = pixelColor.b / 255.0;

    // minimalna i maksymalna wartość RGB
    minColor = min(min(r, g), b);
    maxColor = max(max(r, g), b);

    // kalkulacja luminancji
    hsl.l = (minColor + maxColor) / 2;

    //kalkulacja nasycenia
    hsl.s = calculateSaturation(minColor, maxColor, hsl.l);

    //kalkulacja odcienia
    hsl.h = calculateHue(r, g, b, minColor, maxColor);

    if (hsl.h < 0.0) hsl.h = hsl.h + 360.0;
    if (hsl.h > 360.0) hsl.h = hsl.h - 360.0;

    return hsl;
}
