#include <AdafruitIO.h>
#include <wifi/AdafruitIO_ESP8266.h>

#define IO_USERNAME "pdkary"
#define IO_KEY "adabbdb7e3b54c6ea7d5762b14fa959a"

#define WIFI_SSID "BELL815"
#define WIFI_PASS "26AEACA434EF"

AdafruitIO_ESP8266 io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
