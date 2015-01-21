

#include <letsgoING_Tinydroid.h>
#include <Adafruit_NeoPixel.h>
#include <LGI_QTouch_Tiny.h>


#define PIN 2
#define PIXEL 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL, PIN, NEO_RGB + NEO_KHZ800);


long lastTime=0;
long waitTime = 50;
boolean touched = false;

uint32_t white, red, green, blue;
int numPixel;

QTouchButton Button1(3, 2);


Ardudroid Remote;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  white = strip.Color(250, 250, 250);
  strip.setPixelColor(0, white);  
  strip.show();
  delay(1000);

  Remote.BTtiny_begin(9600);
}

void loop() {
  Remote.readBluetooth();
  strip.setPixelColor(0,Remote.getRed() ,Remote.getGreen() ,Remote.getBlue());  
  strip.show();
}







