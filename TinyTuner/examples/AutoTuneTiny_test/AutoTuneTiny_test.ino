#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <TinyTuner.h>

#define eeAddress 200

SoftwareSerial tinySerial(0, 1);


void setup( void )
{
  //!!!ACHTUNG!!!
  //OSCCAL = EEPROM.read(eeAddress); // Wenn der Attiny eingestellt wurde -> Kommentar  entfernen
  tinySerial.begin(9600);
}

void loop( void )
{
  tinySerial.println("Wenn dieser Text lesbar ist, muss der Attiny nicht parametriert werden");
  tinySerial.print("OSCCAL: ");
  tinySerial.println(OSCCAL, HEX);
  delay(1000);
}





