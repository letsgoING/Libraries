#include <letsgoING_Ardudroid.h>
Ardudroid Remote;


String ModulName = "GroveXY";
String ModulPin  = "0000";

String AlteBaudRate = "38400";
String NeueBaudRate = "9600";


void setup() {
  pinMode(13,OUTPUT);
  
   //Konfiguration start
  digitalWrite(13, HIGH); 

  //Konfiguriere Groove Bluetoothmodul
  Remote.BTgrove_setup(ModulName, ModulPin, AlteBaudRate, NeueBaudRate);

  //Konfiguration fertig
  digitalWrite(13, LOW); 
}

void loop() {
}






