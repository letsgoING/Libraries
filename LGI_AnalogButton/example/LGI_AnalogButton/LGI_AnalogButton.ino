#include <LGI_AnalogButton.h>


AnalogButton Button1(1);

AnalogButton Button2(2);

AnalogButton Button3(3);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Serial.println("Waiting for Button 1...");
Button1.startButton();

}

void loop() {
  // put your main code here, to run repeatedly: 

  Serial.print(" Button 1: ");
  Serial.print(Button1.getButton());
  Serial.print(" Switch 1: ");
  Serial.print(Button1.getSwitch());
  Serial.print("  Button 2: ");
  Serial.print(Button2.getButton());
  Serial.print("  Button 3: ");
  Serial.print(Button3.getButton());
  //Serial.print("  Switch 3: ");
  //Serial.print(Button3.getSwitch());
    Serial.print("Analog: ");
  Serial.println(analogRead(A3));
  
  delay(200);
}
