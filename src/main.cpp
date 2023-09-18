#include <Arduino.h>
#include "Bitcraze_PMW3901.h"

// Using digital pin 10 for chip select
Bitcraze_PMW3901 flow(22);
int16_t deltaX,deltaY;
float volts;
float adc_value;
float distance;
int32_t sumX=0,sumY=0;
#define IRpin 34
uint32_t preT,curT;
float posX=0,posY=0;
void setup()
{
  Serial.begin(115200);
    if (!flow.begin()) {
    Serial.println("Initialization of the flow sensor failed");
    while(1) { }
  }
  preT=millis();
}

void loop()
{

    // Get motion count since last call
  flow.readMotionCount(&deltaX, &deltaY);

  // Serial.print("X: ");

  sumX +=deltaX;
  sumY+=deltaY;
  // Serial.print(deltaX);
  // Serial.print(",");
  // Serial.print(deltaY);
  // Serial.print(",");
  // Serial.print(sumX);
  // Serial.print(",");
  // Serial.print(sumY);
  // Serial.print("\n");
  // delay(100);

  adc_value = analogRead(IRpin);
  volts = adc_value * 0.0008058608;
  distance = 65 * pow(volts, -1.10);
  curT=millis();
  float velx = (distance*42*M_PI/180*deltaX)/((float)(curT-preT)/1000*35);
  float vely = (distance*42*M_PI/180*deltaY)/((float)(curT-preT)/1000*35);
  posX+=velx*(float)(curT-preT)/1000;
  posY+=vely*(float)(curT-preT)/1000;

  Serial.print(velx);
  Serial.print(",");
  Serial.print(vely);
  Serial.print(",");
  Serial.print(posX);
  Serial.print(",");
  Serial.print(posY);
  Serial.print("\n");
  delay(5);
  Serial.print("\n");
  
}


