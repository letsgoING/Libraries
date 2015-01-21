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
	
05.12.2013 Anian Bühler
*/

#include "Arduino.h"


#ifndef _ARDUDROID_
#define _ARDUDROID_

#include <SoftwareSerial.h>

class Ardudroid
{
private:
	//
	char    inputString[14];
	
	int 	RemoteDirection, 
			RemoteSpeed;
	
	uint8_t countData,
			LedRed, 
			LedGreen, 
			LedBlue;
			
	bool	RemoteButton1,
			RemoteButton2,
			RemoteSwitch1,
			RemoteSwitch2,
			LedLight,
			PhoneEvent1,
			PhoneEvent2,
			PhoneEvent3,
			PhoneEvent4,
			PhoneEvent5,
			PhoneEvent6,
			stringComplete;
			
	SoftwareSerial *softSerial;		
    
    
	

public:
	//Konstruktor
	//******************************************************************
	Ardudroid();
	Ardudroid(uint8_t _softRx, uint8_t _softTx);
	//setter
	//******************************************************************   
	void BTsoftSerial_begin(int Baud); 
	void BTbee_begin(int Baud);
	void BTserial_setup(String btName, String btCode);
	void BTserial_begin();
	//getter
	//******************************************************************
	//Fernsteuerung
	int getSpeed();
	int getDirection();
	bool getButton(uint8_t Button);
	//LED_Steuerung
	int getRed();
	int getGreen();
	int getBlue();
	bool getLedSwitch();
	//Monitor
	char getBluetooth();
	//Events
	bool getEvent(uint8_t Event);
		
	//Read Android
	//******************************************************************
	void readBluetooth();
	void getData();

};


#endif;