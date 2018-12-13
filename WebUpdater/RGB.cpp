
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

#endif