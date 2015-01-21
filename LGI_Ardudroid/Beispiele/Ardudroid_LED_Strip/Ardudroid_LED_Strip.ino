
/*************************************
 * Beispiel zur Fernsteuerung eines  *
 * LED-Streifens mit der LGI-App     *
 *************************************/

#include <letsgoING_Ardudroid.h>
#include <RGBdriver.h>

#define CLK 4//pins definitions for the driver        
#define DIO 5

//Erstelle Ardudroid-Objekt
Ardudroid Remote;
//Erstelle RGB-LED-Objekt
RGBdriver LED(CLK,DIO);

void setup() 
{
  //Starte Serielle Kommunikation mit Bluetooth-Modul
  Remote.BTbee_begin(9600); //BTserial_begin(); wenn Bluetooth Serial Modul
}

void loop() 
{
  //Übergebe Werte der Fernsteuerung an LED
  LED.begin(); // begin

  if(Remote.getLedSwitch())//Wenn LED-Schalter aktiviert lese Fernbedienung
    LED.SetColor(Remote.getRed(), Remote.getGreen(), Remote.getBlue()); //Red. first node data 
  else //Sonst Leds aus
    LED.SetColor(0,0,0);

  LED.end();
}


//Lese Daten ein wenn vorhanden
//*******************************
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





