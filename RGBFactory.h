#include "RGB.h"
class RGBFactory{
    public:
        RGBFactory(String hexString);
        RGBFactory(int hexInt);
        RGB build();
    private:
        RGB rgb;
}