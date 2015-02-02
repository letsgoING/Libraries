/*
Klasse zur Kommunikation mit Android Phone / lgI-App:
- Lese Fernsteuerung
	- Speed 
	- Direction
	- Button 1+2 
	- Switch 1+2
- Lese LED-Steuerung
	- Rot
	- Grün
	- Blau
	
10.12.2013 Anian Bühler
16.05.2014 Anian Bühler
*/

#include "letsgoING_Ardudroid.h"

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
	#define SerialAvailable() 0
    #define SerialBegin(X)
	#define SerialPrint(X) 
	#define SerialRead() 0
	#define SerialFlush() 
	#define SerialParseInt()
#else
	#define SerialAvailable() Serial.available()
    #define SerialBegin(X) Serial.begin(X)
	#define SerialPrint(X) Serial.print(X)
	#define SerialRead() Serial.read()
	#define SerialFlush() Serial.flush()
	#define SerialParseInt() Serial.parseInt()
#endif

//Konstruktor
	//******************************************************************
	Ardudroid :: Ardudroid(){	
			RemoteDirection = 0;
			RemoteSpeed		= 0;
			LedRed			= 0;
			LedGreen		= 0;
			LedBlue			= 0;
			countData		= 0;
			internState     = 0;
			btState         = 0;
			
			RemoteButton1	= false;
			RemoteButton2	= false;
			RemoteSwitch1	= false;
			RemoteSwitch2	= false;
			LedLight		= false;
			PhoneState1		= false;
			PhoneState2		= false;
			PhoneState3		= false;
			PhoneState4		= false;
			PhoneState5		= false;
			PhoneState6		= false;
			stringComplete	= false;
	
	}
	
	Ardudroid :: Ardudroid(uint8_t _softRx, uint8_t _softTx){	
			softSerial = new SoftwareSerial(_softRx, _softTx);
		
			RemoteDirection = 0;
			RemoteSpeed		= 0;
			LedRed			= 0;
			LedGreen		= 0;
			LedBlue			= 0;
			countData		= 0;
			internState     = 0;
			btState         = 0;
			
			RemoteButton1	= false;
			RemoteButton2	= false;
			RemoteSwitch1	= false;
			RemoteSwitch2	= false;
			LedLight		= false;
			PhoneState1		= false;
			PhoneState2		= false;
			PhoneState3		= false;
			PhoneState4		= false;
			PhoneState5		= false;
			PhoneState6		= false;
			stringComplete	= false;
	
	}
	
	//setter
	//******************************************************************
	void Ardudroid :: BTsoftSerial_begin(int Baud){//default 9600	
			softSerial->begin(Baud);
	}
	
	
	void Ardudroid :: BTserial_begin(int Baud){//default 9600
			SerialBegin(Baud);
	}
		
	void Ardudroid :: BTgrove_setup(String btName, String btCode, String oldBaud, String newBaud){
	  //Setze neue Baudrate (wenn geaendert)
	  //************************************
	  if(oldBaud.toInt() != newBaud.toInt()){
		Serial.begin(oldBaud.toInt());
		Serial.print("\r\n+STBD="+newBaud+"\r\n");
		Serial.end();
		delay(2000);
	  }

	  //Starte mit neuer Baudrate
	  //*************************
	  Serial.begin(newBaud.toInt());
	  delay(50);

	  Serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	  Serial.print("\r\n+STNA="+btName+"\r\n"); //set the bluetooth name
	  Serial.print("\r\n+STPIN="+btCode+"\r\n");//Set SLAVE pincode
	  Serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
	  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	  
	  delay(2000); // This delay is required.
	  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	  delay(2000); // This delay is required.
	  Serial.flush();
	}
	

	
	
	//getter
//******************************************************************
	//Fernsteuerung
	int Ardudroid :: getSpeed(){
		return this->RemoteSpeed;
	}
	
	int Ardudroid :: getDirection(){
		return this->RemoteDirection;
	}
	
	bool Ardudroid :: getButton(uint8_t Button){
		switch (Button)
		{
			case 1:
				return this->RemoteButton1;
				break;
			
			case 2:
				return this->RemoteButton2;
				break;

			case 3:
				return this->RemoteSwitch1;			
				break;
			
			case 4:
				return this->RemoteSwitch2;
				break;
		}	
	}
	
	
	//LED_Steuerung
	int Ardudroid :: getRed(){
		return this->LedRed;
	}
	
	int Ardudroid :: getGreen(){
		return this->LedGreen;
	}
	
	int Ardudroid :: getBlue(){
		return this->LedBlue;
	}
	
	bool Ardudroid :: getLedSwitch(){
		return this->LedLight;
	}
	
	//States
	bool Ardudroid :: getState(uint8_t State){
		switch (State)
		{
			case 1:
				return this->PhoneState1;
				break;
			
			case 2:
				return this->PhoneState2;
				break;

			case 3:
				return this->PhoneState3;			
				break;
			
			case 4:
				return this->PhoneState4;
				break;
				
			case 5:
				return this->PhoneState5;			
				break;
			
			case 6:
				return this->PhoneState6;
				break;
		}	
	}
		
	//Read from Android
	//******************************************************************
	//Monitor
	char Ardudroid :: readMonitor(){
		char data;
			if(SerialAvailable())
				data = (char)SerialRead();

		return data;
	}
	
	char Ardudroid :: readSoftMonitor(){	
		char data;
			if(softSerial->available())
				data = (char)softSerial->read();

		return data;
	}
	
	void Ardudroid :: readRemote(){	
		while(SerialAvailable()){
			char inChar = (char)SerialRead(); 
			// add it to the inputString:
			inputString[countData] = inChar;
			countData++;

			if (inChar == '\n') {
			  stringComplete = true;
			  countData = 0;
			}
		}
		getData();

	}
	
	void Ardudroid :: readSoftRemote(){    
		while(softSerial->available()){
			char inChar = (char)softSerial->read();
			// add it to the inputString:
			inputString[countData] = inChar;
			countData++;
		
			if (inChar == '\n') {
				stringComplete = true;
				countData = 0;
			}
		}
		getData();	
	}	
	
	int Ardudroid :: readConState(){
		char first, second, third;
		 
		while(SerialAvailable()){
		    //parse return from Grove BTmodul -> returns '+BTSTATE:X' X=1-4
			switch(internState){	
			case 0://check for '+' as prelimiter
				first = SerialRead();			
				if(first =='+') internState++; 	
				break;
			case 1://if first Char = '+' -> check for 'B'
				second = SerialRead();			
				if(second =='+') internState++; 
				break;
			case 2://if second Char = 'B' -> read until ':'
				third = SerialRead();
				if(third ==':') {	//if third = ':' -> read state of Grove BTmodul
				while(!SerialAvailable());
				char state = SerialRead();
					btState = state-48; //convert char to int
					internState = 0;    // go back to first internState
					}
				break;
			}
		}
		return btState;	 //return Grove BTmodule state
	}

	int Ardudroid :: readSoftConState(){
		char first, second, third;
		
		while(softSerial->available()){
			//parse return from Grove BTmodul -> returns '+BTSTATE:X' X=1-4
			switch(internState){
			case 0://check for '+' as prelimiter
				first = softSerial->read();
				if(first =='+') internState++; 
				break;
			case 1://if first Char = '+' -> check for 'B'
				second = softSerial->read();
				if(second =='+') internState++; 
				break;
			case 2://if second Char = 'B' -> read until ':'
				third = softSerial->read();
				if(third ==':') {//if third = ':' -> read state of Grove BTmodul
				while(!softSerial->available());
				char state = softSerial->read();;
					btState = state-48;//convert char to int
					internState = 0;    // go back to first internState
					}
				break;
			}
		}
			
		return btState;	//return Grove BTmodule state

}
	
	//Write to Android
	//******************************************************************
	//Monitor
	void Ardudroid :: printMonitor(char* String){
		SerialPrint(String);
	}

	void Ardudroid :: printSoftMonitor(int Data){
		softSerial->print(Data);
	}
	
	void Ardudroid :: printSoftMonitor(char* String){
		softSerial->write(String);
	}
	void Ardudroid :: printMonitor(int Data){
		SerialPrint(Data);
	}	



	
	//Parse Data
	//******************************************************************
	void Ardudroid :: getData()
	{
		if(stringComplete)
		{
			//adapt Data
			switch (this->inputString[0]-48)
			{
			  //Fernsteuerung
			case 0:
			  // Int aus 3 String-Zahlen
			  this->RemoteSpeed     = (int) (this->inputString[2]-48)*100 + (this->inputString[3]-48)*10 + (this->inputString[4]-48)*1;
			  this->RemoteDirection = (int)(this->inputString[6]-48)*100 + (this->inputString[7]-48)*10 + (this->inputString[8]-48)*1;
			  
			  //Wenn Vorzeichen -
			  if(this->inputString[1] == 45) //Vorzeichen Ivertieren
				this->RemoteSpeed = - this->RemoteSpeed ;
			  //Wenn Vorzeichen -
			  if(inputString[5] != 45) //Vorzeichen Ivertieren
				this->RemoteDirection = - this->RemoteDirection;

			  //Wenn Taster/Schalter aktiv
			  this->RemoteButton1 = (this->inputString[9]  - 48) > 0;
			  this->RemoteButton2 = (this->inputString[10] - 48) > 0;
			  this->RemoteSwitch1 = (this->inputString[11] - 48) > 0;
			  this->RemoteSwitch2 = (this->inputString[12] - 48) > 0;
			  break;

			  //LED Steuerung
			case 1:
			  this->LedRed     = (this->inputString[1]-48)*100 + (this->inputString[2]-48)*10 + (this->inputString[3]-48)*1;
			  this->LedGreen   = (this->inputString[4]-48)*100 + (this->inputString[5]-48)*10 + (this->inputString[6]-48)*1;
			  this->LedBlue    = (this->inputString[7]-48)*100 + (this->inputString[8]-48)*10 + (this->inputString[9]-48)*1;

			  this->LedLight = (this->inputString[10] - 48) > 0; 

			//Wenn Taster/Schalter aktiv
			  this->RemoteButton1 = (this->inputString[11] - 48) > 0;
			  this->RemoteButton2 = (this->inputString[12] - 48) > 0;
			  this->RemoteSwitch1 = (this->inputString[13] - 48) > 0;
			  this->RemoteSwitch2 = (this->inputString[14] - 48) > 0;			  
			  break;

			  //Telefon States
			case 2:

			  this->PhoneState1 = (this->inputString[1]  - 48) > 0;
			  this->PhoneState2 = (this->inputString[2]  - 48) > 0;
			  this->PhoneState3 = (this->inputString[3]  - 48) > 0;
			  this->PhoneState4 = (this->inputString[4]  - 48) > 0;
			  this->PhoneState5 = (this->inputString[5]  - 48) > 0;
			  this->PhoneState6 = (this->inputString[6]  - 48) > 0;
			  break;
			}

			this->stringComplete = false;
		}
	}