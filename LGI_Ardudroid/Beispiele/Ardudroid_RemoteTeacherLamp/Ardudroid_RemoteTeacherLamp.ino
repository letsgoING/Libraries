#include <movingAverage.h>
#include <letsgoING_Ardudroid.h>
#include <RGBdriver.h>
#define CLK 4//pins definitions for the driver        
#define DIO 5

int loudness;
int Red, Green, Blue;

RGBdriver Driver(CLK,DIO);
Ardudroid Remote;
movingAverage average(15);


void serialEvent() 
{
  //Lese Daten ein solange vorhanden
  while(Serial.available()) 
  {
    //lese Fernbedienung
    Remote.readBluetooth();	
  }  
  //Rechne Daten in passende Werte um
  Remote.getData();
}

void setup() 
{
  Driver.begin();    
  Driver.SetColor(0, 0, 0);
  Driver.end();
  
  Remote.BTserial_begin();
  average.clear();
  
  
  //STARTUP LIGHT
  delay(500);
  Driver.begin();
  Driver.SetColor(255, 0, 0);
  Driver.end();
  delay(500);
  Driver.begin();
  Driver.SetColor(0, 255, 0);
  Driver.end();
  delay(500);
  Driver.begin();
  Driver.SetColor(0, 0, 255);
  Driver.end();
  delay(500);
  Driver.begin();
  Driver.SetColor(255, 255, 255);
  Driver.end();
  delay(1000);
  
}

void loop() 
{

  if(Remote.getLedSwitch())//Wenn LED-Schalter aktiviert lese Fernbedienung
  {
    Red   = Remote.getRed();
    Green = Remote.getGreen();
    Blue  = Remote.getBlue();
  }
  else //Sonst
  {
    average.addValue((float)analogRead(A2)); //ca. in Prozent
    loudness = constrain(average.getAverage(), 0, 100);
    Red      = (loudness * 255)/100;
    Green    = ((100-loudness) * 255)/100;
    Blue     = 0;
    delay(10);
  }


  Driver.begin();
  Driver.SetColor(Red, Green, Blue);
  Driver.end();
}

