/*************************************
* Beispiel zur Fernsteuerung eines   *
* LGI-Rovers mit der LGI-App         *
*************************************/


#include <letsgoING_Ardudroid.h>
#include <letsgoING_Drive.h>

//Erstelle Fahrzeug-Objekt
Drive Rover;
//Erstelle Ardudroid-Objekt
Ardudroid Remote;


void setup() 
{
  //Starte Serielle Kommunikation mit Bluetooth-Modul
  Remote.BTbee_begin(9600);
}

void loop() 
{
  //Übergebe Werte der Fernsteuerung an Fahrzeug
  Rover.driveCurve(Remote.getDirection(), Remote.getSpeed());
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

