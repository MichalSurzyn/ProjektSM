#ifndef SM2024DITHERING_H_INCLUDED
#define SM2024DITHERING_H_INCLUDED

void zaktualizujTabliceBayera4();

void bayer4x4RGB();

void bayer4x4BW();

void floydRGB();;

void floydBW();

void setDitheredRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b);

void applyBayerDithering(int screenWidth, int screenHeight);

#endif // SM2024DITHERING_H_INCLUDED
