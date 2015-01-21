#include "Arduino.h"
#include "letsgoING_LEDBar.h"

//LED-Bar Instanz Pin10: gelbes Kabel, Pin9: weisses Kabel
LEDBar TestLEDBar (10, 9);
//Werte vom Infrarotsensor
int sensorValue;
int sensorPin;

void setup()
{
    //Pins
    sensorPin=0;
    pinMode(sensorPin, INPUT);
    
    //Wertebereich
    TestLEDBar.setMapLow(30);
    TestLEDBar.setMapHigh(300);
}

void loop()
{
   //Wert einlesen
   sensorValue=analogRead(sensorPin);
    
   if (sensorValue < 300)
   {
     digitalWrite(4 , HIGH);
     analogWrite(5, 100);
     digitalWrite(7 , HIGH);
     analogWrite(6, 100);
   }
   else
   {
     analogWrite(5, 0);
     analogWrite(6, 0);
   }
	
    //Ausgabe auf LEDs, Richtung von gruen nach rot (0)
    TestLEDBar.analogToStack(sensorValue, 0);
    delay(50);
}

