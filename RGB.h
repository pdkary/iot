class RGB {
    public:
        unsigned char R;
        unsigned char G;
        unsigned char B;
        RGB(unsigned char R,unsigned char G,unsigned char B);
        bool Equals(RGB rgb);
        void logRGB();
        static RGB fromHex(String hexString);
        static RGB fromInt(int hexInt);
}