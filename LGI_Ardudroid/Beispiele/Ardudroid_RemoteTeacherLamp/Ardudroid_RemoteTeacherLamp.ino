#include <movingAverage.h>
#include <letsgoING_Ardudroid.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define PIXEL 1

int loudness;
int Red, Green, Blue;

//Ardudroid
Ardudroid Remote;
//Avg
movingAverage average(15);
//NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL, PIN, NEO_RGB + NEO_KHZ800);

void serialEvent(){
    //lese Fernbedienung
    Remote.readBluetooth();	
}

void setup() 
{
  
  Remote.BTserial_begin();
  average.clear();
  
  //Init NeoPixel
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  //STARTUP LIGHT
  strip.setPixelColor(0, strip.Color(250, 0, 0));  
  strip.show();
  delay(1000);
  strip.setPixelColor(0, strip.Color(0, 250, 0));  
  strip.show();
  delay(1000);
  strip.setPixelColor(0, strip.Color(0, 0, 250));  
  strip.show();
  delay(1000);
  strip.setPixelColor(0, strip.Color(0, 0, 0));  
  strip.show();
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
  
  strip.setPixelColor(0, strip.Color(Red, Green, Blue)); 
  strip.show();
}

