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



//Konstruktor
	//******************************************************************
	Ardudroid :: Ardudroid()
	{	
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
	
		Ardudroid :: Ardudroid(uint8_t _softRx, uint8_t _softTx)
	{	

			#define BT_SoftSerial
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
	void Ardudroid :: BTsoftSerial_begin(int Baud) //default 9600
	{	
		#if defined(BT_SoftSerial)
			softSerial->	begin(Baud);
		#endif
	}
	
	
	void Ardudroid :: BTbee_begin(int Baud) //default 9600
	{
		#ifndef BT_SoftSerial
			Serial.begin(Baud);
		#endif
	}
		
	void Ardudroid :: BTserial_setup(String btName, String btCode)
	{
	  #ifndef BT_SoftSerial
	  Serial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
	  Serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	  
	  Serial.print("\r\n+STNA="+btName+"\r\n"); //set the bluetooth name as "SeeedBTSlave"
	  Serial.print("\r\n+STPIN="+btCode+"\r\n");//Set SLAVE pincode"0000"
	  
	  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	  Serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
	  delay(2000); // This delay is required.
	  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	  //Serial.println("The slave bluetooth is inquirable!");
	  delay(2000); // This delay is required.
	  Serial.flush();
	  #endif
	}
	
	void Ardudroid :: BTserial_begin()
	{
	  #ifndef BT_SoftSerial
	  Serial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
	  Serial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
	  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
	  Serial.print("\r\n+STAUTO=0\r\n"); //  Auto-connection should be forbidden here
	  delay(2000); // This delay is required.
	  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
	  //Serial.println("The slave bluetooth is inquirable!");
	  //delay(2000); // This delay is required.
	  Serial.flush();
	  #endif
	}
	
	
	//getter
	//******************************************************************
	//Fernsteuerung
	int Ardudroid :: getSpeed()
	{
		return this->RemoteSpeed;
	}
	
	int Ardudroid :: getDirection()
	{
		return this->RemoteDirection;
	}
	
	bool Ardudroid :: getButton(uint8_t Button)
	{
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
	int Ardudroid :: getRed()
	{
		return this->LedRed;
	}
	
	int Ardudroid :: getGreen()
	{
		return this->LedGreen;
	}
	
	int Ardudroid :: getBlue()
	{
		return this->LedBlue;
	}
	
	bool Ardudroid :: getLedSwitch()
	{
		return this->LedLight;
	}
	
	//Monitor
	char Ardudroid :: getBluetooth(){
		char data;
		#if defined(BT_SoftSerial)
			if(softSerial->available())
				data =  (char)softSerial->read();
		#else
			if(Serial.available())
				data = (char)Serial.read()
		#endif
		return data;
	}
	
	//Events
	bool Ardudroid :: getEvent(uint8_t Event)
	{
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

	void Ardudroid :: readBluetooth()
	{	
	#if defined(BT_SoftSerial) //|| defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)    
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
	#else
		while(Serial.available(){
			char inChar = (char)Serial.read(); 
			// add it to the inputString:
			inputString[countData] = inChar;
			countData++;

			if (inChar == '\n') {
			  stringComplete = true;
			  countData = 0;
			}
		}
		getData();
	#endif
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