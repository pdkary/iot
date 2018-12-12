#ifndef RGBFactory_h
#define RGBFactory_h

#include "RGB.h"
#include "RGBFactory.h"
#include <Arduino.h>

RGBFactory::RGBFactory(String hexString){
    long number = (long) strtol( &hexString[0], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;
    rgb = RGB(r,g,b);
}
RGBFactory::RGBFactory(int hexInt){
    RGBFactory(String(hexInt,HEX));
}
RGB RGBFactory::build(){
    return rgb;
}