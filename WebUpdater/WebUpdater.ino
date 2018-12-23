#include "config.h"
#include "RGB.h"
#include "RGBFactory.h"

#include <AdafruitIO.h>
#include <ESP8266WiFi.h>

#define RED 13
#define BLUE 12
#define GREEN 14

#define BUTTONPIN 4

int value = 0;


// set up the 'digital' feed
AdafruitIO_Feed *LoveLights = io.feed("LoveLights", "pdkary");
bool onBool = false;

void setRGB(bool R, bool G, bool B){
    digitalWrite(RED,R);
    digitalWrite(RED,G);
    digitalWrite(RED,B);
}

void updateLights(){
  if(digitalRead(BUTTONPIN)){
    value+=1;
    value = value % 8;
  }
  LoveLights->save(value);
  delay(100);
}
void setLights(int dataValue){
  switch(dataValue) {
    case 0:
      setRGB(0,0,0);
      break;
    case 1:
      setRGB(0,0,1);
      break;
    case 2:
      setRGB(0,1,0);
      break;
    case 3:
      setRGB(0,1,1);
      break;
    case 4:
      setRGB(1,0,0);
      break;
    case 5:
      setRGB(1,0,1);
      break;
    case 6:
      setRGB(1,1,0);
      break;
    case 7:
      setRGB(1,1,1);
      break;
  }
}

void handleMessage(AdafruitIO_Data *data) {
  onBool = !onBool;
  int value = data->toInt();
  setLights(value);
  delay(10);
}

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);

  Serial.begin(115200);
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  LoveLights -> onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  LoveLights->get();
}
void loop() {
    io.run();
    updateLights();
}
