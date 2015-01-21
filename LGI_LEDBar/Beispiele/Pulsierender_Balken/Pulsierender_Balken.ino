/*Demoprogramm zur Anzeige von pulsierendem Balken
* 16.07.2013 Michael Grupp
*/
#include "Arduino.h"
#include "letsgoING_LEDBar.h"

//LED-Bar Instanz Pin10: gelbes Kabel, Pin9: weißes Kabel
LEDBar TestLEDBar (10, 9);

void setup()
{   

}

void loop()
{	
    for (int i=0; i<1023; i++) {
      TestLEDBar.analogToStack(i, 0);
    }
    for (int j=1023; j>0; j--) {
      TestLEDBar.analogToStack(j, 0);
    }
}
