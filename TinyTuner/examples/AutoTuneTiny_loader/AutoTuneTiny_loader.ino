
#include <SoftwareSerial.h>

#define mPreStart    0
#define mCalibrating 1
#define mDone        2
#define mWaiting     3
#define mERROR       4

#define LEDpin 9
#define STATEpin 13
#define ERRORpin 12

uint8_t Menu = mPreStart;
uint8_t curOSCCAL = 0;

SoftwareSerial tinySerial(8,11); //RX unused, TX to Attiny Pin0

void setup(){

  pinMode(STATEpin, INPUT);
  pinMode(ERRORpin, INPUT);

  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, LOW);

  Serial.begin(9600);
  tinySerial.begin(9600);

  //GET OSCCAL FROM ATTINY
  Serial.println("Warten auf Attiny...");
  while(!digitalRead(STATEpin));


  //MENU
  Serial.println("**********************************");
  Serial.println(" Attiny bereit fuer Kalibrierung");
  Serial.println(" Zum Starten bitte 's' senden");
  Serial.println("**********************************");
  Serial.println("\n\n");
  digitalWrite(LEDpin, HIGH);
}


void loop(){

  switch(Menu){

  case  mCalibrating:
    if(digitalRead(STATEpin)){
      tinySerial.print("x");
      digitalWrite(LEDpin, !digitalRead(LEDpin));
      delay(300);
    }
    else{
      Menu = mDone; 
    }
    break;

  case mDone:
    if(digitalRead(ERRORpin)){
      Serial.println("**********************************");
      Serial.println(" Attiny ist Kalibriert");
      Serial.println("**********************************");
      Serial.println("\n\n");
      Serial.println("Fuer die naechste Kalibrierung den Arduino resetten...");
      Menu = mWaiting;
    }
    else{
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      Serial.println("Attiny Kalibrierung ist fehlgeschlagen");
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      Serial.println("\n\n");
      Serial.println("Fuer eine erneute Kalibrierung den Arduino resetten...");
      Menu = mERROR;
    }
    break;  

  case mWaiting:
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    delay(1000);
    break;

  case mERROR:
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    delay(100);
    break;
  }

}

void serialEvent(){
  char input = Serial.read();
  if(Menu == mPreStart && (input == 's' || input == 'S')){
    Menu = mCalibrating;
  } 
}











