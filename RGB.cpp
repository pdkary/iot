
#ifndef RGB_h
#define RGB_h

#include "RGB.h"
#include <Arduino.h>

RGB::RGB(unsigned char r,unsigned char g,unsigned char b){
    R = r;
    G = g;
    B = b;
}
bool RGB::Equals(RGB rgb){
    bool r = rgb.R == R;
    bool g = rgb.G == G;
    bool b = rgb.B == B;
    return r && g && b;
}
void RGB::logRGB(){
    Serial.printf("R:%d\tG:%d\tB:%d",R,G,B);
}

static RGB RGB::fromHex(String hexString){
    long number = (long) strtol( &hexString[0], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;
    return RGB(r,g,b);
}

static RGB RGB::fromInt(int hexInt){
    return RGB::fromHex(String(hexInt,HEX));
}


#endif