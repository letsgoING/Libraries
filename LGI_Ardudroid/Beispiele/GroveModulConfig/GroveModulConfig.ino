

String ModulName = "GroveXY";
String ModulPin  = "0000";

String AlteBaudRate = "38400";
String NeueBaudRate = "9600";

void setup() {

  pinMode(13,OUTPUT);

  //Konfiguration start
  //**********************
  digitalWrite(13, HIGH); 

  //Setze neue Baudrate (wenn geaendert)
  //************************************
  if(AlteBaudRate.toInt() != NeueBaudRate.toInt()){
    Serial.begin(AlteBaudRate.toInt());
    Serial.print("\r\n+STBD="+NeueBaudRate+"\r\n");
    Serial.end();
    delay(2000);
  }

  //Starte mit neuer Baudrate
  //*************************
  Serial.begin(NeueBaudRate.toInt());
  delay(50);

  Serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  Serial.print("\r\n+STNA="+ModulName+"\r\n"); //set the bluetooth name
  Serial.print("\r\n+STPIN="+ModulPin+"\r\n");//Set SLAVE pincode
  Serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  
  delay(2000); // This delay is required.
  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  delay(2000); // This delay is required.
  Serial.flush();

  //Konfiguration fertig
  //**********************
  digitalWrite(13, LOW); 
}

void loop() {
}





