#include "RGB.h"
class RGBFactory{
    public:
        int R;
        int G;
        int B;
        RGBFactory(String hexString);
        RGBFactory(int hexInt);
        RGB build();
    private:
        RGB rgb;
}