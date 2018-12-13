#ifndef RGBFactory_h
#define RGBFactory_h

#include "RGB.h"
#include "RGBFactory.h"
#include <Arduino.h>

RGBFactory::RGBFactory(String hexString){
    long number = (long) strtol( &hexString[0], NULL, 16);
    R = number >> 16;
    G = number >> 8 & 0xFF;
    B = number & 0xFF;
    rgb = RGB(R,G,B);
}
RGBFactory::RGBFactory(int hexInt){
    RGBFactory(String(hexInt,HEX));
}
RGB RGBFactory::build(){
    return RGB(R,G,B);
}

#endif