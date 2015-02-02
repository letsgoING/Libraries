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
			LedBlue,
			internState,
			btState;
			
	bool	RemoteButton1,
			RemoteButton2,
			RemoteSwitch1,
			RemoteSwitch2,
			LedLight,
			PhoneState1,
			PhoneState2,
			PhoneState3,
			PhoneState4,
			PhoneState5,
			PhoneState6,
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
	void BTserial_begin(int Baud);
	void BTgrove_setup(String btName, String btCode, String oldBaud, String newBaud);
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
	
	//Events
	bool getState(uint8_t State);
		
	//Read from Android
	//******************************************************************
	//Monitor
	char readMonitor();
	char readSoftMonitor();
	//Remote
	void readRemote();
	void readSoftRemote();
	
	//wait for Connection
	int readConState();
	int readSoftConState();
	
	//Write to Android
	//******************************************************************
	//Monitor
	void printSoftMonitor(char* String);
	void printSoftMonitor(int Data);	
	void printMonitor(char* String);
	void printMonitor(int Data);	
	
	//Parse Data
	//******************************************************************
	void getData();

};


#endif;