#include <EEPROM.h>
#include <TinyTuner.h>

#define STATEpin   2
#define ERRORpin   1
#define LEDpin     3

#define eeAddress 200

void setup( void )
{
  pinMode( STATEpin, OUTPUT );
  pinMode( ERRORpin, OUTPUT );
  pinMode( LEDpin, OUTPUT );
}

void loop( void )
{
  Tiny84Tuner tt;
  bool KeepGoing = true;

  digitalWrite( STATEpin, HIGH );
  digitalWrite( ERRORpin, HIGH );

  while ( KeepGoing )
  {
    KeepGoing = tt.update();

    for ( uint8_t i=0; i < 2; ++i )
    {    
      digitalWrite( LEDpin, ! digitalRead( LEDpin ) );
      delay( 100 );
    }
  }
  
  uint8_t Temp = OSCCAL;
  EEPROM.write( eeAddress, Temp );

  if ( EEPROM.read(eeAddress) == Temp )
  {
    digitalWrite( STATEpin, LOW );
  }
  else
  {
    digitalWrite( ERRORpin, LOW );
  }
  while ( 1 );
}



