#ifndef SM2024COLORMODELS_H_INCLUDED
#define SM2024COLORMODELS_H_INCLUDED

#include "SM2024Variables.h"


YUV getYUV(int xx, int yy);

void setYUV (int xx, int yy, float y, float u, float v);

YIQ getYIQ(int xx, int yy);

void setYIQ (int xx, int yy, float y, float i, float q);

YCbCr getYCbCr(int xx, int yy);

void setYCbCr (int xx, int yy, float y, float cb, float cr);

HSL getHSL(int xx, int yy);

void setHSL(int xx, int yy, float h, float s, float l);

#endif // SM2024COLORMODELS_H_INCLUDED
