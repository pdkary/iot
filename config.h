
#define IO_USERNAME "pdkary"
#define IO_KEY "adabbdb7e3b54c6ea7d5762b14fa959a"

#define WIFI_SSID "BELL374"
#define WIFI_PASS "4F6CFD1CDEC3"

#include <AdafruitIO.h>
#include <AdafruitIO_Wifi.h>

AdafruitIO_ESP8266 io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
