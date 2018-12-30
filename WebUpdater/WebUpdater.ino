#include "config.h"
#include <AdafruitIO.h>

#define RED 13
#define BLUE 12
#define GREEN 14

#define DELAY_TIME 500

AdafruitIO_Feed *LoveLights = io.feed("LoveLights", "pdkary");

void setRGB(bool R, bool G, bool B) {
  digitalWrite(RED, R);
  digitalWrite(GREEN, G);
  digitalWrite(BLUE, B);
}

void setLights(int dataValue) {
  switch (dataValue) {
    case 0:
      setRGB(0, 0, 0);
      break;
    case 1:
      setRGB(0, 0, 1);
      break;
    case 2:
      setRGB(0, 1, 0);
      break;
    case 3:
      setRGB(0, 1, 1);
      break;
    case 4:
      setRGB(1, 0, 0);
      break;
    case 5:
      setRGB(1, 0, 1);
      break;
    case 6:
      setRGB(1, 1, 0);
      break;
    case 7:
      setRGB(1, 1, 1);
      break;
  }
}

void handleMessage(AdafruitIO_Data *data) {
  int value = data->toInt();
  setLights(value);
  delay(DELAY_TIME);
}

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  Serial.begin(115200);
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  LoveLights -> onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(DELAY_TIME);
  }

  Serial.println();
  Serial.println(io.statusText());
  LoveLights->get();
}
void loop() {
  io.run();
}
