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
#include "RGB.h"

#include <AdafruitIO.h>
#include <ESP8266WiFi.h>

#define RED 2
#define BLUE 4
#define GREEN 5

int value = 0;


// set up the 'digital' feed
AdafruitIO_Feed *AssistiveCallButtons = io.feed("LoveLights", "pdkary");
bool onBool = false;

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
  RGB rgb = RGB.fromInt(value);
  rgb.logRGB();
  delay(100);
}

void handleMessage(AdafruitIO_Data *data) {
  onBool = !onBool;
  int value = data->toInt();
  RGB rgb = RGB.fromInt(value);
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
