// Remote Control with the Huzzah + Adafruit IO
//
// LED Board
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Richard Albritton, based on original code by Tony DiCola for Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
/************************ Example Starts Here *******************************/
#include "config.h"

#include <AdafruitIO.h>
#include <ESP8266WiFi.h>

#define RED 2
#define BLUE 4
#define GREEN 5

int value = 0;


// set up the 'digital' feed
AdafruitIO_Feed *AssistiveCallButtons = io.feed("LoveLights", "pdkary");
bool onBool = false;

class RGB
{
  public:
    unsigned char R;
    unsigned char G;
    unsigned char B;

    RGB(unsigned char r, unsigned char g, unsigned char b)
    {
      R = r;
      G = g;
      B = b;
    }
    bool Equals(RGB rgb)
    {
      return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
    }
    void logRGB() {
      Serial.printf("R:%d\tG:%d\tB:%d\n", R, G, B);
    }
};

RGB colorConverter(int hexInt)
{
    String hexstring = String(hexInt,HEX);
    long number = (long) strtol( &hexstring[0], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;
    return RGB(r,g,b);
}

void updateLights(){
  if (digitalRead(GREEN)) {
    value += 400000;
    AssistiveCallButtons->save(value);
  };
  if (digitalRead(BLUE)) {
    value -= 400000;
    AssistiveCallButtons->save(value);
  }
  if (value < 0) {
    value = 0;
  }
  if (value > 16777215) {
    value = 16777215;
  }
  RGB rgb = colorConverter(value);
  rgb.logRGB();
  delay(100);
}

void handleMessage(AdafruitIO_Data *data) {
  onBool = !onBool;
  int value = data->toInt();
  RGB rgb = colorConverter(value);
  // delay in-between reads for stability
  delay(1);
}

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(BLUE, INPUT);
  pinMode(GREEN, INPUT);

  Serial.begin(115200);
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  AssistiveCallButtons -> onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  AssistiveCallButtons->get();
}
void loop() {
    io.run();
    updateLights();
}
