
//TODO:
// 1- Serial Monitor öffnen und mit AT+UART? die Baudrate auslesen (NL und CR einschalten)
// 2- Programm auf Arduino laden 
// 3- Nach dem Programm-Upload das BT-Modul einstecken und den Arduino neu starten
//!!!!!!!ACHTUNG: bei dem BTBeePro-Modul muss der MODE-Button waehrend des gesamten Vorgangs gedrueckt sein
//(solange bis die LED13 angeht)
// 4- LED13 leuchtet -> SetUp erfolgreich oder LED13 blinkt   -> SetUp fehlerhaft

///////////////////////////////////////////////////////////////
//HIER Name, PinCode und Baudrate einstellen
///////////////////////////////////////////////////////////////
String BTname      = "BTbeePro";
String BTpassword  = "0000";     //Hier nur Ziffern
int StartBTbaud    = 9600;      // BTbeePro -> 38400; HC-05 -> 57600  
///////////////////////////////////////////////////////////////
//HIER NICHTS AENDERN!!
///////////////////////////////////////////////////////////////

String BTbaud      = "9600";

boolean configDone(){
  byte First = ' ';
  byte Second = ' ';
  //wait for answer
  boolean modulOK = false;
  while(!modulOK){
    while(Serial.available()){
      First  = Serial.read();
      if(First=='O'){
        byte Second = Serial.read();
        if(Second=='K');
        modulOK = true;
      }
    }
  }
  return modulOK;
};

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  delay(4000);

  Serial.begin(StartBTbaud); 

  //check module state
  Serial.print("AT\r\n");

  //if module not OK -> reset
  while(!configDone())
    Serial.print("AT+Reset\r\n");

  delay(1000);


  Serial.print("AT+Name="+BTname+"\r\n");
  //if module not OK
  if(!configDone()){
    while(true){
      digitalWrite(13,HIGH);
      delay(500);
      digitalWrite(13,LOW);
      delay(500);
    }
  }


  Serial.print("AT+PSWD="+BTpassword+"\r\n");
  //if module not OK
  if(!configDone()){
    while(true){
      digitalWrite(13,HIGH);
      delay(500);
      digitalWrite(13,LOW);
      delay(500);
    }
  }

  Serial.print("AT+UART="+BTbaud+",1,0\r\n");
  //if module not OK
  if(!configDone()){
    while(true){
      digitalWrite(13,HIGH);
      delay(500);
      digitalWrite(13,LOW);
      delay(500);
    }
  }

  digitalWrite(13,HIGH);
}

void loop() {
}







