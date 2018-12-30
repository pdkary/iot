#include "DroidConfig.h"
#include <AdafruitIO.h>
#include <Servo.h> 

#define BOTTOMPIN 2
#define TOPPIN 4

#define DELAY_TIME 100

AdafruitIO_Feed *TopServo = io.feed("TopServo", "pdkary");
AdafruitIO_Feed *BottomServo = io.feed("BottomServo", "pdkary");

Servo topServo;
Servo bottomServo;

void handleMessage(AdafruitIO_Data *data,Servo servo){
  int value = data->toInt();
  Serial.println(value);
  servo.write(value);
  delay(DELAY_TIME);
}
void handleTop(AdafruitIO_Data *data){
  handleMessage(data,topServo);
}
void handleBottom(AdafruitIO_Data *data){
  handleMessage(data,bottomServo);
}
void setup() {
  pinMode(BOTTOMPIN,OUTPUT);
  pinMode(TOPPIN,OUTPUT);

  topServo.attach(TOPPIN);
  bottomServo.attach(BOTTOMPIN);

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
