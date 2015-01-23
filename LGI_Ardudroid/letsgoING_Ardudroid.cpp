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
#else
	#define SerialAvailable() Serial.available()
    #define SerialBegin(X) Serial.begin(X)
	#define SerialPrint(X) Serial.print(X)
	#define SerialRead() Serial.read()
	#define SerialFlush() Serial.flush()
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
			
			RemoteButton1	= false;
			RemoteButton2	= false;
			RemoteSwitch1	= false;
			RemoteSwitch2	= false;
			LedLight		= false;
			PhoneEvent1		= false;
			PhoneEvent2		= false;
			PhoneEvent3		= false;
			PhoneEvent4		= false;
			PhoneEvent5		= false;
			PhoneEvent6		= false;
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
			
			RemoteButton1	= false;
			RemoteButton2	= false;
			RemoteSwitch1	= false;
			RemoteSwitch2	= false;
			LedLight		= false;
			PhoneEvent1		= false;
			PhoneEvent2		= false;
			PhoneEvent3		= false;
			PhoneEvent4		= false;
			PhoneEvent5		= false;
			PhoneEvent6		= false;
			stringComplete	= false;
	
	}
	
	//setter
	//******************************************************************
	void Ardudroid :: BTsoftSerial_begin(int Baud){//default 9600	
			softSerial->begin(Baud);
	}
	
	void Ardudroid :: BTsoftGrove_begin(){	
			softSerial-> begin(38400);
			
			softSerial-> print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
		    softSerial-> print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
		    softSerial-> print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
		    delay(2000); // This delay is required.
		    softSerial-> print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
		    //Serial-> println("The slave bluetooth is inquirable!");
		    delay(2000); // This delay is required.
		    softSerial-> flush();  
	}
	
	
	void Ardudroid :: BTserial_begin(int Baud){//default 9600
			SerialBegin(Baud);
	}
		
	void Ardudroid :: BTgrove_setup(String btName, String btCode){
	  SerialBegin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
	  SerialPrint("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	  
	  SerialPrint("\r\n+STNA="+btName+"\r\n"); //set the bluetooth name as "SeeedBTSlave"
	  SerialPrint("\r\n+STPIN="+btCode+"\r\n");//Set SLAVE pincode"0000"
	  
	  SerialPrint("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	  SerialPrint("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
	  delay(2000); // This delay is required.
	  SerialPrint("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	  //SerialPrint("The slave bluetooth is inquirable!");
	  delay(2000); // This delay is required.
	  SerialFlush();
	}
	
	void Ardudroid :: BTgrove_begin(){
	  SerialBegin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
	  SerialPrint("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	  SerialPrint("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	  SerialPrint("\r\n+STAUTO=0\r\n"); //  Auto-connection should be forbidden here
	  delay(2000); // This delay is required.
	  SerialPrint("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	  //SerialPrint.println("The slave bluetooth is inquirable!");
	  //delay(2000); // This delay is required.
	  SerialFlush();
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
	
	//Events
	bool Ardudroid :: getEvent(uint8_t Event){
		switch (Event)
		{
			case 1:
				return this->PhoneEvent1;
				break;
			
			case 2:
				return this->PhoneEvent2;
				break;

			case 3:
				return this->PhoneEvent3;			
				break;
			
			case 4:
				return this->PhoneEvent4;
				break;
				
			case 5:
				return this->PhoneEvent5;			
				break;
			
			case 6:
				return this->PhoneEvent6;
				break;
		}	
	}
		
	//Read Android
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

			  //Telefon Events
			case 2:

			  this->PhoneEvent1 = (this->inputString[1]  - 48) > 0;
			  this->PhoneEvent2 = (this->inputString[2]  - 48) > 0;
			  this->PhoneEvent3 = (this->inputString[3]  - 48) > 0;
			  this->PhoneEvent4 = (this->inputString[4]  - 48) > 0;
			  this->PhoneEvent5 = (this->inputString[5]  - 48) > 0;
			  this->PhoneEvent6 = (this->inputString[6]  - 48) > 0;
			  break;
			}

			this->stringComplete = false;
		}
	}