#include "DroidConfig.h"
#include <AdafruitIO.h>

#define BOTTOMPIN 1
#define TOPPIN 2
#define ANALOG A0

#define DELAY_TIME 100

AdafruitIO_Feed *TopServo = io.feed("TopServo", "pdkary");
AdafruitIO_Feed *BottomServo = io.feed("BottomServo", "pdkary");

void handleMessage(AdafruitIO_Data *data,bool isTop){
  digitalWrite(TOPPIN,isTop);
  digitalWrite(BOTTOMPIN,!isTop);
  int value = data->toInt();
  analogWrite(ANALOG,value);
  delay(DELAY_TIME);
}
void handleTop(AdafruitIO_Data *data){
  handleMessage(data,true);
}
void handleBottom(AdafruitIO_Data *data){
  handleMessage(data,false);
}
void setup() {
  pinMode(BOTTOMPIN,OUTPUT);
  pinMode(TOPPIN,OUTPUT);
  pinMode(ANALOG,OUTPUT);  

  Serial.begin(115200);
  while(!Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  TopServo -> onMessage(handleTop);
  BottomServo -> onMessage(handleBottom);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(DELAY_TIME);
  }
  Serial.println();
  Serial.println(io.statusText());
  TopServo->get();
  BottomServo->get();
}

void loop() {
  io.run();
}
