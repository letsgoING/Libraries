#include <letsgoING_Ardudroid.h>
#include <Adafruit_NeoPixel.h>
#include <LGI_QTouch.h>

//Umschalten des Bluetoothsystems
#define BTSystem 2 //0->Arduino(HardwareSerial)	1->Arduino(SoftSerial)	2->Attiny(SoftSerial)

//Definition der NeoPixel-Pins
#define PIN 2
#define PIXEL 1


//NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL, PIN, NEO_RGB + NEO_KHZ800);
//Einlesen der Pixelanzahl
int numPixel = strip.numPixels();

//QTouch
QTouchButton Button(A3, A2);
boolean touched = false;

//For Wait without delay()
long lastTime=0;
long waitTime = 50;

//BT Instanzen anlegen
#if BTSystem == 0
//Arduino HardwareSerial
Ardudroid Remote;	

void serialEvent(){
  //Auslesen der Fernsteuerung
  Remote.readRemote();	
}
#elif BTsystem == 1
//Arduino SoftwareSerial
Ardudroid Remote(4,5);  //DO NOT USE PIN0 AND PIN1
#else
//Attiny SoftwareSerial
Ardudroid Remote(0,1);
#endif


void setup() {
  //Init NeoPixel
  strip.begin();
  strip.show(); // Initialisiere alle Pixel "aus"

  for( int i = 0; i < numPixel; i++){
    strip.setPixelColor(i, 250, 250, 250);   // setze Farbe über RGB-Wert
  }
  strip.show(); //gebe Pixelfarbe aus
  delay(1000);

  //Init Button
  Button.init();

  //BT COM
#if BTSystem == 0
  //Arduino HardwareSerial
  Remote.BTserial_begin(9600);	
#else
  //Arduino and Attiny SoftwareSerial
  Remote.BTsoftSerial_begin(9600);
#endif
}

void loop() {

  //IF SoftSerial is used	
#if BTSystem
  Remote.readSoftRemote();
#endif

  //Set Color if Button touched
  for( int i = 0; i < numPixel; i++){
    strip.setPixelColor(i, 250, 250, 250);   // setze Farbe über RGB-Wert
  }
  strip.show(); //gebe Pixelfarbe aus
}


